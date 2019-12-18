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
struct urwlock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMTX_OP_RW_UNLOCK ; 
 int _umtx_op_err (struct urwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
__thr_rwlock_unlock(struct urwlock *rwlock)
{

	return (_umtx_op_err(rwlock, UMTX_OP_RW_UNLOCK, 0, NULL, NULL));
}