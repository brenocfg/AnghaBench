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
 int /*<<< orphan*/  LC_MESSAGES ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 char* strerror (long) ; 
 long strtol (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 

int 
main(int argc, char **argv)
{
	char *cp;
	char *errstr;
	long errnum;

	(void) setlocale(LC_MESSAGES, "");
	if (argc != 2)
		usage();

	errno = 0;

	errnum = strtol(argv[1], &cp, 0);

	if (errno != 0)
		err(1, NULL);

	if ((errstr = strerror(errnum)) == NULL) 
		err(1, NULL);

	printf("%s\n", errstr);

	exit(0);
}