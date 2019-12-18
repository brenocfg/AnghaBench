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
typedef  int /*<<< orphan*/  lcond ;

/* Variables and functions */
 int /*<<< orphan*/  A_GETCOND ; 
 int /*<<< orphan*/  A_OLDGETCOND ; 
 scalar_t__ EINVAL ; 
 int auditon (int /*<<< orphan*/ ,...) ; 
 scalar_t__ errno ; 

int
audit_get_cond(int *cond)
{
	int ret;

	ret = auditon(A_GETCOND, cond, sizeof(*cond));
#ifdef A_OLDGETCOND
	if ((0 != ret) && EINVAL == errno) {
		long lcond = *cond;

		ret = auditon(A_OLDGETCOND, &lcond, sizeof(lcond));
		*cond = (int)lcond;
	}
#endif
	return (ret);
}