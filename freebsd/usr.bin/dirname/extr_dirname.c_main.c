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
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 char* dirname (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char **argv)
{
	char *p;
	int ch;

	if (caph_limit_stdio() < 0 || caph_enter() < 0)
		err(1, "capsicum");

	while ((ch = getopt(argc, argv, "")) != -1)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc < 1)
		usage();

	while (argc--) {
		if ((p = dirname(*argv)) == NULL)
			err(1, "%s", *argv);
		argv++;
		(void)printf("%s\n", p);
	}
	exit(0);
}