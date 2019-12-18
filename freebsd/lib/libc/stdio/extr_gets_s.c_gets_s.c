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
typedef  scalar_t__ rsize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  FLOCKFILE_CANCELSAFE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FUNLOCKFILE_CANCELSAFE () ; 
 scalar_t__ RSIZE_MAX ; 
 int /*<<< orphan*/  __throw_constraint_handler_s (char*,int /*<<< orphan*/ ) ; 
 char* _gets_s (char*,scalar_t__) ; 
 int /*<<< orphan*/  stdin ; 

char *
gets_s(char *buf, rsize_t n)
{
	char *ret;
	if (buf == NULL) {
		__throw_constraint_handler_s("gets_s : str is NULL", EINVAL);
		return(NULL);
	} else if (n > RSIZE_MAX) {
		__throw_constraint_handler_s("gets_s : n > RSIZE_MAX",
			EINVAL);
		return(NULL);
	} else if (n == 0) {
		__throw_constraint_handler_s("gets_s : n == 0", EINVAL);
		return(NULL);
	}

	FLOCKFILE_CANCELSAFE(stdin);
	ret = _gets_s(buf, n);
	FUNLOCKFILE_CANCELSAFE();
	return (ret);
}