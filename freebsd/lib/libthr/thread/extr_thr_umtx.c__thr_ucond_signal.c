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
struct ucond {int /*<<< orphan*/  c_has_waiters; } ;

/* Variables and functions */
 int /*<<< orphan*/  UMTX_OP_CV_SIGNAL ; 
 int _umtx_op_err (struct ucond*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
_thr_ucond_signal(struct ucond *cv)
{

	if (!cv->c_has_waiters)
		return (0);
	return (_umtx_op_err(cv, UMTX_OP_CV_SIGNAL, 0, NULL, NULL));
}