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
 int chdir (char const*) ; 
 int /*<<< orphan*/  die (char*) ; 
 char* getenv (char*) ; 

__attribute__((used)) static void cd_to_homedir(void)
{
	const char *home = getenv("HOME");
	if (!home)
		die("could not determine user's home directory; HOME is unset");
	if (chdir(home) == -1)
		die("could not chdir to user's home directory");
}