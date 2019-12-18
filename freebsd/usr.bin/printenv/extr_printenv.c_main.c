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
 char** environ ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  memcmp (char*,char*,size_t) ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char *cp, **ep;
	size_t len;
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

	if (argc == 0) {
		for (ep = environ; *ep; ep++)
			(void)printf("%s\n", *ep);
		exit(0);
	}
	len = strlen(*argv);
	for (ep = environ; *ep; ep++)
		if (!memcmp(*ep, *argv, len)) {
			cp = *ep + len;
			if (*cp == '=') {
				(void)printf("%s\n", cp + 1);
				exit(0);
			}
		}
	exit(1);
}