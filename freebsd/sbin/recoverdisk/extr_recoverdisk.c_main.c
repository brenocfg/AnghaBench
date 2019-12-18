#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ time_t ;
struct stat {scalar_t__ st_size; int /*<<< orphan*/  st_mode; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_5__ {scalar_t__ len; scalar_t__ start; int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFFILEMODE ; 
 int /*<<< orphan*/  DIOCGMEDIASIZE ; 
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int /*<<< orphan*/  DIOCGSTRIPESIZE ; 
 scalar_t__ EINVAL ; 
 scalar_t__ ENXIO ; 
 size_t MIN (scalar_t__,scalar_t__) ; 
 int O_CREAT ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  PRINT_HEADER ; 
 int /*<<< orphan*/  PRINT_STATUS (scalar_t__,size_t,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SIGINT ; 
 scalar_t__ S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISCHR (int /*<<< orphan*/ ) ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int aborting ; 
 int bigsize ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int fstat (int,struct stat*) ; 
 scalar_t__ ftruncate (int,scalar_t__) ; 
 int getopt (int,char* const*,char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  list ; 
 TYPE_1__* lp ; 
 int /*<<< orphan*/  lumps ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int medsize ; 
 int minsize ; 
 int /*<<< orphan*/  new_lump (size_t,size_t,int) ; 
 int open (char* const,int,...) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 size_t pread (int,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 size_t pwrite (int,int /*<<< orphan*/ *,size_t,scalar_t__) ; 
 scalar_t__ read_worklist (scalar_t__) ; 
 int rounddown (int,int) ; 
 int /*<<< orphan*/ * rworklist ; 
 int /*<<< orphan*/  save_worklist () ; 
 int /*<<< orphan*/  sighandler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 void* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 void* strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/ * wworklist ; 

int
main(int argc, char * const argv[])
{
	int ch;
	int fdr, fdw;
	off_t t, d, start, len;
	size_t i, j;
	int error, state;
	u_char *buf;
	u_int sectorsize;
	off_t stripesize;
	time_t t1, t2;
	struct stat sb;
	u_int n, snapshot = 60;

	while ((ch = getopt(argc, argv, "b:r:w:s:")) != -1) {
		switch (ch) {
		case 'b':
			bigsize = strtoul(optarg, NULL, 0);
			break;
		case 'r':
			rworklist = strdup(optarg);
			if (rworklist == NULL)
				err(1, "Cannot allocate enough memory");
			break;
		case 's':
			snapshot = strtoul(optarg, NULL, 0);
			break;
		case 'w':
			wworklist = strdup(optarg);
			if (wworklist == NULL)
				err(1, "Cannot allocate enough memory");
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}
	argc -= optind;
	argv += optind;

	if (argc < 1 || argc > 2)
		usage();

	fdr = open(argv[0], O_RDONLY);
	if (fdr < 0)
		err(1, "Cannot open read descriptor %s", argv[0]);

	error = fstat(fdr, &sb);
	if (error < 0)
		err(1, "fstat failed");
	if (S_ISBLK(sb.st_mode) || S_ISCHR(sb.st_mode)) {
		error = ioctl(fdr, DIOCGSECTORSIZE, &sectorsize);
		if (error < 0)
			err(1, "DIOCGSECTORSIZE failed");

		error = ioctl(fdr, DIOCGSTRIPESIZE, &stripesize);
		if (error == 0 && stripesize > sectorsize)
			sectorsize = stripesize;

		minsize = sectorsize;
		bigsize = rounddown(bigsize, sectorsize);

		error = ioctl(fdr, DIOCGMEDIASIZE, &t);
		if (error < 0)
			err(1, "DIOCGMEDIASIZE failed");
	} else {
		t = sb.st_size;
	}

	if (bigsize < minsize)
		bigsize = minsize;

	for (ch = 0; (bigsize >> ch) > minsize; ch++)
		continue;
	medsize = bigsize >> (ch / 2);
	medsize = rounddown(medsize, minsize);

	fprintf(stderr, "Bigsize = %zu, medsize = %zu, minsize = %zu\n",
	    bigsize, medsize, minsize);

	buf = malloc(bigsize);
	if (buf == NULL)
		err(1, "Cannot allocate %zu bytes buffer", bigsize);

	if (argc > 1) {
		fdw = open(argv[1], O_WRONLY | O_CREAT, DEFFILEMODE);
		if (fdw < 0)
			err(1, "Cannot open write descriptor %s", argv[1]);
		if (ftruncate(fdw, t) < 0)
			err(1, "Cannot truncate output %s to %jd bytes",
			    argv[1], (intmax_t)t);
	} else
		fdw = -1;

	if (rworklist != NULL) {
		d = read_worklist(t);
	} else {
		new_lump(0, t, 0);
		d = 0;
	}
	if (wworklist != NULL)
		signal(SIGINT, sighandler);

	t1 = 0;
	start = len = i = state = 0;
	PRINT_HEADER;
	n = 0;
	for (;;) {
		lp = TAILQ_FIRST(&lumps);
		if (lp == NULL)
			break;
		while (lp->len > 0 && !aborting) {
			/* These are only copied for printing stats */
			start = lp->start;
			len = lp->len;
			state = lp->state;

			i = MIN(lp->len, (off_t)bigsize);
			if (lp->state == 1)
				i = MIN(lp->len, (off_t)medsize);
			if (lp->state > 1)
				i = MIN(lp->len, (off_t)minsize);
			time(&t2);
			if (t1 != t2 || lp->len < (off_t)bigsize) {
				PRINT_STATUS(start, i, len, state, d, t);
				t1 = t2;
				if (++n == snapshot) {
					save_worklist();
					n = 0;
				}
			}
			if (i == 0) {
				errx(1, "BOGUS i %10jd", (intmax_t)i);
			}
			fflush(stdout);
			j = pread(fdr, buf, i, lp->start);
			if (j == i) {
				d += i;
				if (fdw >= 0)
					j = pwrite(fdw, buf, i, lp->start);
				else
					j = i;
				if (j != i)
					printf("\nWrite error at %jd/%zu\n",
					    lp->start, i);
				lp->start += i;
				lp->len -= i;
				continue;
			}
			printf("\n%jd %zu failed (%s)\n",
			    lp->start, i, strerror(errno));
			if (errno == EINVAL) {
				printf("read() size too big? Try with -b 131072");
				aborting = 1;
			}
			if (errno == ENXIO)
				aborting = 1;
			new_lump(lp->start, i, lp->state + 1);
			lp->start += i;
			lp->len -= i;
		}
		if (aborting) {
			save_worklist();
			return (0);
		}
		TAILQ_REMOVE(&lumps, lp, list);
		free(lp);
	}
	PRINT_STATUS(start, i, len, state, d, t);
	save_worklist();
	printf("\nCompleted\n");
	return (0);
}