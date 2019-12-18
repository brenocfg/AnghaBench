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
 int EOF ; 
 int /*<<< orphan*/  abort () ; 
 int getchar () ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int strtol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	int c, count, linepos, maxcount, pretty, radix;

	maxcount = 0;
	pretty = 0;
	radix = 10;
	while ((c = getopt(argc, argv, "n:sx")) != -1) {
		switch (c) {
		case 'n':	/* Max. number of bytes per line. */
			maxcount = strtol(optarg, NULL, 10);
			break;
		case 's':	/* Be more style(9) comliant. */
			pretty = 1;
			break;
		case 'x':	/* Print hexadecimal numbers. */
			radix = 16;
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	if (argc > 0)
		printf("%s\n", argv[0]);
	count = linepos = 0;
	while((c = getchar()) != EOF) {
		if (count) {
			putchar(',');
			linepos++;
		}
		if ((maxcount == 0 && linepos > 70) ||
		    (maxcount > 0 && count >= maxcount)) {
			putchar('\n');
			count = linepos = 0;
		}
		if (pretty) {
			if (count) {
				putchar(' ');
				linepos++;
			} else {
				putchar('\t');
				linepos += 8;
			}
		}
		switch (radix) {
		case 10:
			linepos += printf("%d", c);
			break;
		case 16:
			linepos += printf("0x%02x", c);
			break;
		default:
			abort();
		}
		count++;
	}
	putchar('\n');
	if (argc > 1)
		printf("%s\n", argv[1]);
	return (0);
}