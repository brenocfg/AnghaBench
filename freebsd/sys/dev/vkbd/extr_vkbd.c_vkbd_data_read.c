#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ cc; int* q; scalar_t__ head; } ;
struct TYPE_6__ {int /*<<< orphan*/  ks_wsel; TYPE_2__ ks_inq; } ;
typedef  TYPE_1__ vkbd_state_t ;
typedef  TYPE_2__ vkbd_queue_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PZERO ; 
 int /*<<< orphan*/  VKBD_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ nitems (int*) ; 
 int /*<<< orphan*/  selwakeuppri (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wakeup (TYPE_2__*) ; 

__attribute__((used)) static int
vkbd_data_read(vkbd_state_t *state, int wait)
{
	vkbd_queue_t	*q = &state->ks_inq;
	int		 c;

	VKBD_LOCK_ASSERT(state, MA_OWNED);

	if (q->cc == 0)
		return (-1);

	/* get first code from the queue */
	q->cc --;
	c = q->q[q->head ++];
	if (q->head == nitems(q->q))
		q->head = 0;

	/* wakeup ks_inq writers/poll()ers */
	selwakeuppri(&state->ks_wsel, PZERO + 1);
	wakeup(q);

	return (c);
}