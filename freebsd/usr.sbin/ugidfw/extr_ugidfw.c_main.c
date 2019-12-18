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
 int /*<<< orphan*/  add_rule (int,char**) ; 
 int /*<<< orphan*/  list_rules () ; 
 int /*<<< orphan*/  remove_rule (int,char**) ; 
 int /*<<< orphan*/  set_rule (int,char**) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{

	if (argc < 2)
		usage();

	if (strcmp("add", argv[1]) == 0) {
		add_rule(argc-2, argv+2);
	} else if (strcmp("list", argv[1]) == 0) {
		if (argc != 2)
			usage();
		list_rules();
	} else if (strcmp("set", argv[1]) == 0) {
		set_rule(argc-2, argv+2);
	} else if (strcmp("remove", argv[1]) == 0) {
		remove_rule(argc-2, argv+2);
	} else
		usage();

	return (0);
}