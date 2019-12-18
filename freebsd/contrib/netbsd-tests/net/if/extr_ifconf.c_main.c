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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  atoi (char*) ; 
 int /*<<< orphan*/  help () ; 
 int /*<<< orphan*/  show_interfaces (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  show_number_of_entries () ; 
 scalar_t__ strcmp (char*,char*) ; 

int
main(int argc, char *argv[])
{
	if (argc < 2)
		help();

	if (strcmp(argv[1], "total") == 0) {
		show_number_of_entries();
	} else if (strcmp(argv[1], "list") == 0) {
		if (argc == 2)
			show_interfaces(0);
		else if (argc == 3)
			show_interfaces(atoi(argv[2]));
		else
			help();
	} else
		help();

	return EXIT_SUCCESS;
}