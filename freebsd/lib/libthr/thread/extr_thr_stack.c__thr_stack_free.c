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
struct stack {scalar_t__ stacksize; scalar_t__ guardsize; int /*<<< orphan*/ * stackaddr; } ;
struct pthread_attr {int flags; int stacksize_attr; int guardsize_attr; int /*<<< orphan*/ * stackaddr_attr; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct stack*,int /*<<< orphan*/ ) ; 
 scalar_t__ THR_STACK_DEFAULT ; 
 int THR_STACK_USER ; 
 scalar_t__ _thr_guard_default ; 
 int /*<<< orphan*/  dstackq ; 
 int /*<<< orphan*/  mstackq ; 
 int /*<<< orphan*/  qe ; 
 void* round_up (int) ; 

void
_thr_stack_free(struct pthread_attr *attr)
{
	struct stack *spare_stack;

	if ((attr != NULL) && ((attr->flags & THR_STACK_USER) == 0)
	    && (attr->stackaddr_attr != NULL)) {
		spare_stack = (struct stack *)
			((char *)attr->stackaddr_attr +
			attr->stacksize_attr - sizeof(struct stack));
		spare_stack->stacksize = round_up(attr->stacksize_attr);
		spare_stack->guardsize = round_up(attr->guardsize_attr);
		spare_stack->stackaddr = attr->stackaddr_attr;

		if (spare_stack->stacksize == THR_STACK_DEFAULT &&
		    spare_stack->guardsize == _thr_guard_default) {
			/* Default stack/guard size. */
			LIST_INSERT_HEAD(&dstackq, spare_stack, qe);
		} else {
			/* Non-default stack/guard size. */
			LIST_INSERT_HEAD(&mstackq, spare_stack, qe);
		}
		attr->stackaddr_attr = NULL;
	}
}