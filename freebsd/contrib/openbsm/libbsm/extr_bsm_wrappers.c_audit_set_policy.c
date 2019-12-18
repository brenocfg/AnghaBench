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
typedef  int /*<<< orphan*/  lpolicy ;

/* Variables and functions */
 int /*<<< orphan*/  A_OLDSETPOLICY ; 
 int /*<<< orphan*/  A_SETPOLICY ; 
 scalar_t__ EINVAL ; 
 int auditon (int /*<<< orphan*/ ,...) ; 
 scalar_t__ errno ; 

int 
audit_set_policy(int *policy)
{
	int ret;

	ret = auditon(A_SETPOLICY, policy, sizeof(*policy));
#ifdef A_OLDSETPOLICY
	if ((0 != ret) && (EINVAL == errno)){
		long lpolicy = (long)*policy;

		ret = auditon(A_OLDSETPOLICY, &lpolicy, sizeof(lpolicy)); 
		*policy = (int)lpolicy;
	}
#endif
	return (ret);
}