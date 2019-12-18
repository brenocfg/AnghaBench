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
 int CMD_OK ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 int optind ; 
 int optreset ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* unargv (int,char**) ; 

__attribute__((used)) static int
command_echo(int argc, char *argv[])
{
	char	*s;
	int	nl, ch;

	nl = 0;
	optind = 1;
	optreset = 1;
	while ((ch = getopt(argc, argv, "n")) != -1) {
		switch (ch) {
		case 'n':
			nl = 1;
			break;
		case '?':
		default:
			/* getopt has already reported an error */
			return (CMD_OK);
		}
	}
	argv += (optind);
	argc -= (optind);

	s = unargv(argc, argv);
	if (s != NULL) {
		printf("%s", s);
		free(s);
	}
	if (!nl)
		printf("\n");
	return (CMD_OK);
}