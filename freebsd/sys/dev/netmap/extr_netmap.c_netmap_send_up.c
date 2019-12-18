#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mbuf {int dummy; } ;
struct mbq {int dummy; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_LEN (struct mbuf*) ; 
 int NM_DEBUG_HOST ; 
 struct mbuf* mbq_dequeue (struct mbq*) ; 
 int /*<<< orphan*/  mbq_fini (struct mbq*) ; 
 int netmap_debug ; 
 struct mbuf* nm_os_send_up (struct ifnet*,struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  nm_prinf (char*,struct mbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netmap_send_up(struct ifnet *dst, struct mbq *q)
{
	struct mbuf *m;
	struct mbuf *head = NULL, *prev = NULL;

	/* Send packets up, outside the lock; head/prev machinery
	 * is only useful for Windows. */
	while ((m = mbq_dequeue(q)) != NULL) {
		if (netmap_debug & NM_DEBUG_HOST)
			nm_prinf("sending up pkt %p size %d", m, MBUF_LEN(m));
		prev = nm_os_send_up(dst, m, prev);
		if (head == NULL)
			head = prev;
	}
	if (head)
		nm_os_send_up(dst, NULL, head);
	mbq_fini(q);
}