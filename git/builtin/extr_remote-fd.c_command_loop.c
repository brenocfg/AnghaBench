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
 int MAXCOMMAND ; 
 scalar_t__ bidirectional_transfer_loop (int,int) ; 
 int /*<<< orphan*/  die (char*,...) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fgets (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static void command_loop(int input_fd, int output_fd)
{
	char buffer[MAXCOMMAND];

	while (1) {
		size_t i;
		if (!fgets(buffer, MAXCOMMAND - 1, stdin)) {
			if (ferror(stdin))
				die("Input error");
			return;
		}
		/* Strip end of line characters. */
		i = strlen(buffer);
		while (i > 0 && isspace(buffer[i - 1]))
			buffer[--i] = 0;

		if (!strcmp(buffer, "capabilities")) {
			printf("*connect\n\n");
			fflush(stdout);
		} else if (!strncmp(buffer, "connect ", 8)) {
			printf("\n");
			fflush(stdout);
			if (bidirectional_transfer_loop(input_fd,
				output_fd))
				die("Copying data between file descriptors failed");
			return;
		} else {
			die("Bad command: %s", buffer);
		}
	}
}