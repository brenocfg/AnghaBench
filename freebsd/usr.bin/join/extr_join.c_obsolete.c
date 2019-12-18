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
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memmove (char*,char*,size_t) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 size_t strlen (char*) ; 
 size_t strspn (char*,char*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static void
obsolete(char **argv)
{
	size_t len;
	char **p, *ap, *t;

	while ((ap = *++argv) != NULL) {
		/* Return if "--". */
		if (ap[0] == '-' && ap[1] == '-')
			return;
		/* skip if not an option */
		if (ap[0] != '-')
			continue;
		switch (ap[1]) {
		case 'a':
			/*
			 * The original join allowed "-a", which meant the
			 * same as -a1 plus -a2.  POSIX 1003.2, Draft 11.2
			 * only specifies this as "-a 1" and "a -2", so we
			 * have to use another option flag, one that is
			 * unlikely to ever be used or accidentally entered
			 * on the command line.  (Well, we could reallocate
			 * the argv array, but that hardly seems worthwhile.)
			 */
			if (ap[2] == '\0' && (argv[1] == NULL ||
			    (strcmp(argv[1], "1") != 0 &&
			    strcmp(argv[1], "2") != 0))) {
				ap[1] = '\01';
				warnx("-a option used without an argument; "
				    "reverting to historical behavior");
			}
			break;
		case 'j':
			/*
			 * The original join allowed "-j[12] arg" and "-j arg".
			 * Convert the former to "-[12] arg".  Don't convert
			 * the latter since getopt(3) can handle it.
			 */
			switch(ap[2]) {
			case '1':
				if (ap[3] != '\0')
					goto jbad;
				ap[1] = '1';
				ap[2] = '\0';
				break;
			case '2':
				if (ap[3] != '\0')
					goto jbad;
				ap[1] = '2';
				ap[2] = '\0';
				break;
			case '\0':
				break;
			default:
jbad:				errx(1, "illegal option -- %s", ap);
				usage();
			}
			break;
		case 'o':
			/*
			 * The original join allowed "-o arg arg".
			 * Convert to "-o arg -o arg".
			 */
			if (ap[2] != '\0')
				break;
			for (p = argv + 2; *p; ++p) {
				if (p[0][0] == '0' || ((p[0][0] != '1' &&
				    p[0][0] != '2') || p[0][1] != '.'))
					break;
				len = strlen(*p);
				if (len - 2 != strspn(*p + 2, "0123456789"))
					break;
				if ((t = malloc(len + 3)) == NULL)
					err(1, NULL);
				t[0] = '-';
				t[1] = 'o';
				memmove(t + 2, *p, len + 1);
				*p = t;
			}
			argv = p - 1;
			break;
		}
	}
}