#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t c_class; int c_flag; struct TYPE_3__* c_next; int /*<<< orphan*/  c_done_cv; } ;
typedef  TYPE_1__ callb_t ;
typedef  scalar_t__ callb_id_t ;
struct TYPE_4__ {int /*<<< orphan*/  ct_lock; TYPE_1__* ct_freelist; TYPE_1__** ct_first_cb; } ;

/* Variables and functions */
 int CALLB_EXECUTING ; 
 int CALLB_FREE ; 
 int /*<<< orphan*/  CE_WARN ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,void*) ; 
 TYPE_2__* ct ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

int
callb_delete(callb_id_t id)
{
	callb_t **pp;
	callb_t *me = (callb_t *)id;

	mutex_enter(&ct->ct_lock);

	for (;;) {
		pp = &ct->ct_first_cb[me->c_class];
		while (*pp != NULL && *pp != me)
			pp = &(*pp)->c_next;

#ifdef DEBUG
		if (*pp != me) {
			cmn_err(CE_WARN, "callb delete bogus entry 0x%p",
			    (void *)me);
			mutex_exit(&ct->ct_lock);
			return (-1);
		}
#endif /* DEBUG */

		/*
		 * It is not allowed to delete a callb in the middle of
		 * executing otherwise, the callb_execute() will be confused.
		 */
		if (!(me->c_flag & CALLB_EXECUTING))
			break;

		cv_wait(&me->c_done_cv, &ct->ct_lock);
	}
	/* relink the class list */
	*pp = me->c_next;

	/* clean up myself and return the free callb to the head of freelist */
	me->c_flag = CALLB_FREE;
	me->c_next = ct->ct_freelist;
	ct->ct_freelist = me;

	mutex_exit(&ct->ct_lock);
	return (0);
}