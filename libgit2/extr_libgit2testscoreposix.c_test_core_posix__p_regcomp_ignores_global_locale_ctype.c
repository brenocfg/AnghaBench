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
typedef  int /*<<< orphan*/  regex_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_CTYPE ; 
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  REG_EXTENDED ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  p_regcomp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regfree (int /*<<< orphan*/ *) ; 
 char* setlocale (int /*<<< orphan*/ ,char const*) ; 

void test_core_posix__p_regcomp_ignores_global_locale_ctype(void)
{
	regex_t preg;
	int error = 0;

	const char* oldlocale = setlocale(LC_CTYPE, NULL);

	if (!setlocale(LC_CTYPE, "UTF-8") &&
	    !setlocale(LC_CTYPE, "c.utf8") &&
			!setlocale(LC_CTYPE, "en_US.UTF-8"))
		cl_skip();

	if (MB_CUR_MAX == 1) {
		setlocale(LC_CTYPE, oldlocale);
		cl_fail("Expected locale to be switched to multibyte");
	}

	p_regcomp(&preg, "[\xc0-\xff][\x80-\xbf]", REG_EXTENDED);
	regfree(&preg);

	setlocale(LC_CTYPE, oldlocale);

	cl_must_pass(error);
}