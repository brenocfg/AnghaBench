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
 int /*<<< orphan*/  command_loop (int,int) ; 
 int /*<<< orphan*/  die (char*) ; 
 scalar_t__ strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage_msg ; 

int cmd_remote_fd(int argc, const char **argv, const char *prefix)
{
	int input_fd = -1;
	int output_fd = -1;
	char *end;

	if (argc != 3)
		usage(usage_msg);

	input_fd = (int)strtoul(argv[2], &end, 10);

	if ((end == argv[2]) || (*end != ',' && *end != '/' && *end))
		die("Bad URL syntax");

	if (*end == '/' || !*end) {
		output_fd = input_fd;
	} else {
		char *end2;
		output_fd = (int)strtoul(end + 1, &end2, 10);

		if ((end2 == end + 1) || (*end2 != '/' && *end2))
			die("Bad URL syntax");
	}

	command_loop(input_fd, output_fd);
	return 0;
}