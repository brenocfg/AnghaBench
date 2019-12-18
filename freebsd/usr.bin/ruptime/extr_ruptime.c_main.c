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
 int /*<<< orphan*/  _PATH_RWHODIR ; 
 scalar_t__ chdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dirp ; 
 int /*<<< orphan*/  err (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int hscmp (void const*,void const*) ; 
 int lcmp (void const*,void const*) ; 
 int /*<<< orphan*/ * opendir (char*) ; 
 scalar_t__ optind ; 
 int rflg ; 
 int /*<<< orphan*/  ruptime (char*,int,int (*) (void const*,void const*)) ; 
 int tcmp (void const*,void const*) ; 
 int ucmp (void const*,void const*) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int (*cmp)(const void *, const void *);
	int aflg, ch;

	aflg = 0;
	cmp = hscmp;
	while ((ch = getopt(argc, argv, "alrut")) != -1)
		switch (ch) {
		case 'a':
			aflg = 1;
			break;
		case 'l':
			cmp = lcmp;
			break;
		case 'r':
			rflg = -1;
			break;
		case 't':
			cmp = tcmp;
			break;
		case 'u':
			cmp = ucmp;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (chdir(_PATH_RWHODIR) || (dirp = opendir(".")) == NULL)
		err(1, "%s", _PATH_RWHODIR);

	ruptime(*argv, aflg, cmp);
	while (*argv++ != NULL) {
		if (*argv == NULL)
			break;
		ruptime(*argv, aflg, cmp);
	}
	exit(0);
}