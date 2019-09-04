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
 char* REP1024 (char*) ; 
 char* REP16 (char*) ; 
 int /*<<< orphan*/  check_basename (char*,char*) ; 

void test_core_path__01_basename(void)
{
	check_basename(NULL, ".");
	check_basename("", ".");
	check_basename("a", "a");
	check_basename("/", "/");
	check_basename("/usr", "usr");
	check_basename("/usr/", "usr");
	check_basename("/usr/lib", "lib");
	check_basename("/usr/lib//", "lib");
	check_basename("usr/lib", "lib");

	check_basename(REP16("/abc"), "abc");
	check_basename(REP1024("/abc"), "abc");
}