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

/* Variables and functions */
 int /*<<< orphan*/  YPLOCK () ; 
 int /*<<< orphan*/  YPUNLOCK () ; 
 char* _yp_domain ; 
 scalar_t__ yp_bind_locked (char*) ; 
 scalar_t__ yp_get_default_domain_locked (char**) ; 
 int /*<<< orphan*/  yp_unbind_locked (char*) ; 

int
_yp_check(char **dom)
{
	char *unused;

	YPLOCK();
	if (_yp_domain[0]=='\0')
		if (yp_get_default_domain_locked(&unused)) {
			YPUNLOCK();
			return (0);
		}

	if (dom)
		*dom = _yp_domain;

	if (yp_bind_locked(_yp_domain) == 0) {
		yp_unbind_locked(_yp_domain);
		YPUNLOCK();
		return (1);
	}
	YPUNLOCK();
	return (0);
}