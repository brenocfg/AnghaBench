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
 int /*<<< orphan*/  add_internet_password () ; 
 int /*<<< orphan*/  delete_internet_password () ; 
 int /*<<< orphan*/  die (char const*) ; 
 int /*<<< orphan*/  find_internet_password () ; 
 int /*<<< orphan*/  read_credential () ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

int main(int argc, const char **argv)
{
	const char *usage =
		"usage: git credential-osxkeychain <get|store|erase>";

	if (!argv[1])
		die(usage);

	read_credential();

	if (!strcmp(argv[1], "get"))
		find_internet_password();
	else if (!strcmp(argv[1], "store"))
		add_internet_password();
	else if (!strcmp(argv[1], "erase"))
		delete_internet_password();
	/* otherwise, ignore unknown action */

	return 0;
}