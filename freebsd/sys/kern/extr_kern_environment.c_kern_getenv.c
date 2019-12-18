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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  KENV_MNAMELEN ; 
 scalar_t__ KENV_MVALLEN ; 
 int /*<<< orphan*/  M_KENV ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 char* _getenv_static (char const*) ; 
 scalar_t__ dynamic_kenv ; 
 scalar_t__ getenv_string (char const*,char*,int) ; 
 char* strdup (char*,int /*<<< orphan*/ ) ; 

char *
kern_getenv(const char *name)
{
	char buf[KENV_MNAMELEN + 1 + KENV_MVALLEN + 1];
	char *ret;

	if (dynamic_kenv) {
		if (getenv_string(name, buf, sizeof(buf))) {
			ret = strdup(buf, M_KENV);
		} else {
			ret = NULL;
			WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
			    "getenv");
		}
	} else
		ret = _getenv_static(name);
	return (ret);
}