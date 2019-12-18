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
struct ifnet {int /*<<< orphan*/  if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IF_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IF_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _IF_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 

__attribute__((used)) static void
pflogstart(struct ifnet *ifp)
{
	struct mbuf *m;

	for (;;) {
		IF_LOCK(&ifp->if_snd);
		_IF_DEQUEUE(&ifp->if_snd, m);
		IF_UNLOCK(&ifp->if_snd);

		if (m == NULL)
			return;
		else
			m_freem(m);
	}
}