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
typedef  scalar_t__ u64 ;
struct ia64_sal_retval {int dummy; } ;

/* Variables and functions */
 scalar_t__ IA64_SAL_OEMFUNC_MAX ; 
 scalar_t__ IA64_SAL_OEMFUNC_MIN ; 
 int /*<<< orphan*/  SAL_CALL_REENTRANT (struct ia64_sal_retval,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

int
ia64_sal_oemcall_reentrant(struct ia64_sal_retval *isrvp, u64 oemfunc,
			   u64 arg1, u64 arg2, u64 arg3, u64 arg4, u64 arg5,
			   u64 arg6, u64 arg7)
{
	if (oemfunc < IA64_SAL_OEMFUNC_MIN || oemfunc > IA64_SAL_OEMFUNC_MAX)
		return -1;
	SAL_CALL_REENTRANT(*isrvp, oemfunc, arg1, arg2, arg3, arg4, arg5, arg6,
			   arg7);
	return 0;
}