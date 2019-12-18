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
 int /*<<< orphan*/  INTOFF ; 
 int /*<<< orphan*/  INTON ; 
 int /*<<< orphan*/  LC_ALL ; 
 char** argptr ; 
 char* end_fmt ; 
 int /*<<< orphan*/  escape (char*,int,size_t*) ; 
 int /*<<< orphan*/  fwrite (char*,int,int,int /*<<< orphan*/ ) ; 
 char** gargv ; 
 int getopt (int,char**,char*) ; 
 char** maxargv ; 
 size_t myargc ; 
 char** myargv ; 
 int /*<<< orphan*/  nextopt (char*) ; 
 scalar_t__ optind ; 
 char* printf_doformat (char*,int*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	size_t len;
	int end, rval;
	char *format, *fmt, *start;
#ifndef SHELL
	int ch;

	(void) setlocale(LC_ALL, "");
#endif

#ifdef SHELL
	nextopt("");
	argc -= argptr - argv;
	argv = argptr;
#else
	while ((ch = getopt(argc, argv, "")) != -1)
		switch (ch) {
		case '?':
		default:
			usage();
			return (1);
		}
	argc -= optind;
	argv += optind;
#endif

	if (argc < 1) {
		usage();
		return (1);
	}

#ifdef SHELL
	INTOFF;
#endif
	/*
	 * Basic algorithm is to scan the format string for conversion
	 * specifications -- once one is found, find out if the field
	 * width or precision is a '*'; if it is, gather up value.  Note,
	 * format strings are reused as necessary to use up the provided
	 * arguments, arguments of zero/null string are provided to use
	 * up the format string.
	 */
	fmt = format = *argv;
	escape(fmt, 1, &len);		/* backslash interpretation */
	rval = end = 0;
	gargv = ++argv;

	for (;;) {
		maxargv = gargv;

		myargv = gargv;
		for (myargc = 0; gargv[myargc]; myargc++)
			/* nop */;
		start = fmt;
		while (fmt < format + len) {
			if (fmt[0] == '%') {
				fwrite(start, 1, fmt - start, stdout);
				if (fmt[1] == '%') {
					/* %% prints a % */
					putchar('%');
					fmt += 2;
				} else {
					fmt = printf_doformat(fmt, &rval);
					if (fmt == NULL || fmt == end_fmt) {
#ifdef SHELL
						INTON;
#endif
						return (fmt == NULL ? 1 : rval);
					}
					end = 0;
				}
				start = fmt;
			} else
				fmt++;
			if (gargv > maxargv)
				maxargv = gargv;
		}
		gargv = maxargv;

		if (end == 1) {
			warnx("missing format character");
#ifdef SHELL
			INTON;
#endif
			return (1);
		}
		fwrite(start, 1, fmt - start, stdout);
		if (!*gargv) {
#ifdef SHELL
			INTON;
#endif
			return (rval);
		}
		/* Restart at the beginning of the format string. */
		fmt = format;
		end = 1;
	}
	/* NOTREACHED */
}