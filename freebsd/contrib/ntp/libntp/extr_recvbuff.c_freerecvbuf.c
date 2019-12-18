#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ used; } ;
typedef  TYPE_1__ recvbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_SLIST (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK () ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  UNLOCK () ; 
 int /*<<< orphan*/  free_recv_list ; 
 int /*<<< orphan*/  free_recvbufs ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
freerecvbuf(recvbuf_t *rb)
{
	if (rb) {
		LOCK();
		rb->used--;
		if (rb->used != 0)
			msyslog(LOG_ERR, "******** freerecvbuff non-zero usage: %d *******", rb->used);
		LINK_SLIST(free_recv_list, rb, link);
		free_recvbufs++;
		UNLOCK();
	}
}