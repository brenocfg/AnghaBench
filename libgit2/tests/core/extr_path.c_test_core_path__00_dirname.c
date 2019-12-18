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
 char* REP15 (char*) ; 
 char* REP16 (char*) ; 
 int /*<<< orphan*/  check_dirname (char*,char*) ; 

void test_core_path__00_dirname(void)
{
	check_dirname(NULL, ".");
	check_dirname("", ".");
	check_dirname("a", ".");
	check_dirname("/", "/");
	check_dirname("/usr", "/");
	check_dirname("/usr/", "/");
	check_dirname("/usr/lib", "/usr");
	check_dirname("/usr/lib/", "/usr");
	check_dirname("/usr/lib//", "/usr");
	check_dirname("usr/lib", "usr");
	check_dirname("usr/lib/", "usr");
	check_dirname("usr/lib//", "usr");
	check_dirname(".git/", ".");

	check_dirname(REP16("/abc"), REP15("/abc"));

#ifdef GIT_WIN32
	check_dirname("C:/", "C:/");
	check_dirname("C:", "C:/");
	check_dirname("C:/path/", "C:/");
	check_dirname("C:/path", "C:/");
	check_dirname("//computername/", "//computername/");
	check_dirname("//computername", "//computername/");
	check_dirname("//computername/path/", "//computername/");
	check_dirname("//computername/path", "//computername/");
	check_dirname("//computername/sub/path/", "//computername/sub");
	check_dirname("//computername/sub/path", "//computername/sub");
#endif
}