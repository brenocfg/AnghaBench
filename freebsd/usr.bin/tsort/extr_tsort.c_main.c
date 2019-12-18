#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* b_buf; int b_bsize; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  add_arc (char*,char*) ; 
 int debug ; 
 int /*<<< orphan*/  err (int,char*,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int getc (int /*<<< orphan*/ *) ; 
 int getopt (int,char**,char*) ; 
 void* grow_buf (int*,int) ; 
 scalar_t__ isspace (int) ; 
 int longest ; 
 scalar_t__ optind ; 
 int quiet ; 
 int /*<<< orphan*/ * stdin ; 
 int /*<<< orphan*/  tsort () ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	BUF *b;
	int c, n;
	FILE *fp;
	int bsize, ch, nused;
	BUF bufs[2];

	fp = NULL;
	while ((ch = getopt(argc, argv, "dlq")) != -1)
		switch (ch) {
		case 'd':
			debug = 1;
			break;
		case 'l':
			longest = 1;
			break;
		case 'q':
			quiet = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	switch (argc) {
	case 0:
		fp = stdin;
		break;
	case 1:
		if ((fp = fopen(*argv, "r")) == NULL)
			err(1, "%s", *argv);
		break;
	default:
		usage();
	}

	for (b = bufs, n = 2; --n >= 0; b++)
		b->b_buf = grow_buf(NULL, b->b_bsize = 1024);

	/* parse input and build the graph */
	for (n = 0, c = getc(fp);;) {
		while (c != EOF && isspace(c))
			c = getc(fp);
		if (c == EOF)
			break;

		nused = 0;
		b = &bufs[n];
		bsize = b->b_bsize;
		do {
			b->b_buf[nused++] = c;
			if (nused == bsize)
				b->b_buf = grow_buf(b->b_buf, bsize *= 2);
			c = getc(fp);
		} while (c != EOF && !isspace(c));

		b->b_buf[nused] = '\0';
		b->b_bsize = bsize;
		if (n)
			add_arc(bufs[0].b_buf, bufs[1].b_buf);
		n = !n;
	}
	(void)fclose(fp);
	if (n)
		errx(1, "odd data count");

	/* do the sort */
	tsort();
	exit(0);
}