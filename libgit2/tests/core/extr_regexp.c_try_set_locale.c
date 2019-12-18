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
 int MB_CUR_MAX ; 
 int /*<<< orphan*/  cl_fail (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/ * old_locales ; 
 int /*<<< orphan*/  setlocale (int,char*) ; 

__attribute__((used)) static void try_set_locale(int category)
{
#if LC_ALL > 0
	old_locales[category] = setlocale(category, NULL);
#endif

	if (!setlocale(category, "UTF-8") &&
	    !setlocale(category, "c.utf8") &&
	    !setlocale(category, "en_US.UTF-8"))
		cl_skip();

	if (MB_CUR_MAX == 1)
		cl_fail("Expected locale to be switched to multibyte");
}