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
 int /*<<< orphan*/  audump_class () ; 
 int /*<<< orphan*/  audump_class_r () ; 
 int /*<<< orphan*/  audump_control () ; 
 int /*<<< orphan*/  audump_event () ; 
 int /*<<< orphan*/  audump_event_r () ; 
 int /*<<< orphan*/  audump_user () ; 
 int /*<<< orphan*/  audump_user_r () ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{

	if (argc != 2)
		usage();

	if (strcmp(argv[1], "class") == 0)
		audump_class();
	else if (strcmp(argv[1], "class_r") == 0)
		audump_class_r();
	else if (strcmp(argv[1], "control") == 0)
		audump_control();
	else if (strcmp(argv[1], "event") == 0)
		audump_event();
	else if (strcmp(argv[1], "event_r") == 0)
		audump_event_r();
	else if (strcmp(argv[1], "user") == 0)
		audump_user();
	else if (strcmp(argv[1], "user_r") == 0)
		audump_user_r();
	else
		usage();

	return (0);
}