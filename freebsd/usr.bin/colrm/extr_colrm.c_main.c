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
typedef  scalar_t__ u_long ;

/* Variables and functions */
 int /*<<< orphan*/  LC_ALL ; 
 scalar_t__ TAB ; 
#define  WEOF 128 
 int /*<<< orphan*/  check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int getopt (int,char**,char*) ; 
 int getwchar () ; 
 scalar_t__ optind ; 
 int const putwchar (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strtol (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int wcwidth (int) ; 

int
main(int argc, char *argv[])
{
	u_long column, start, stop;
	int ch, width;
	char *p;

	setlocale(LC_ALL, "");

	while ((ch = getopt(argc, argv, "")) != -1)
		switch(ch) {
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	start = stop = 0;
	switch(argc) {
	case 2:
		stop = strtol(argv[1], &p, 10);
		if (stop <= 0 || *p)
			errx(1, "illegal column -- %s", argv[1]);
		/* FALLTHROUGH */
	case 1:
		start = strtol(argv[0], &p, 10);
		if (start <= 0 || *p)
			errx(1, "illegal column -- %s", argv[0]);
		break;
	case 0:
		break;
	default:
		usage();
	}

	if (stop && start > stop)
		errx(1, "illegal start and stop columns");

	for (column = 0;;) {
		switch (ch = getwchar()) {
		case WEOF:
			check(stdin);
			break;
		case '\b':
			if (column)
				--column;
			break;
		case '\n':
			column = 0;
			break;
		case '\t':
			column = (column + TAB) & ~(TAB - 1);
			break;
		default:
			if ((width = wcwidth(ch)) > 0)
				column += width;
			break;
		}

		if ((!start || column < start || (stop && column > stop)) &&
		    putwchar(ch) == WEOF)
			check(stdout);
	}
}