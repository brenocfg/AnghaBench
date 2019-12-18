#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int off_t ;
typedef  char* intmax_t ;
struct TYPE_10__ {int fts_info; int fts_bignum; int fts_level; char* fts_path; TYPE_2__* fts_parent; TYPE_1__* fts_statp; int /*<<< orphan*/  fts_errno; } ;
struct TYPE_9__ {int fts_bignum; } ;
struct TYPE_8__ {int st_size; int st_blocks; int st_nlink; } ;
typedef  TYPE_3__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
 int Aflag ; 
 int DEV_BSIZE ; 
 scalar_t__ ERANGE ; 
 int FTS_COMFOLLOW ; 
#define  FTS_D 134 
#define  FTS_DC 133 
#define  FTS_DNR 132 
#define  FTS_DP 131 
#define  FTS_ERR 130 
 int FTS_LOGICAL ; 
#define  FTS_NS 129 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
 int FTS_XDEV ; 
 int INT_MAX ; 
 int /*<<< orphan*/  LC_ALL ; 
 int /*<<< orphan*/  SIGINFO ; 
#define  SI_OPT 128 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ UNITS_2 ; 
 scalar_t__ UNITS_SI ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int blocksize ; 
 int cblocksize ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expand_number (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ *) ; 
 TYPE_3__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getbsize (int*,int*) ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ hflag ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  ignoreadd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignoreclean () ; 
 int /*<<< orphan*/  ignorep (TYPE_3__*) ; 
 int /*<<< orphan*/  ignores ; 
 int /*<<< orphan*/  info ; 
 int /*<<< orphan*/  linkchk (TYPE_3__*) ; 
 int /*<<< orphan*/  long_options ; 
 int nodumpflag ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prthumanval (int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  siginfo ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

int
main(int argc, char *argv[])
{
	FTS		*fts;
	FTSENT		*p;
	off_t		savednumber, curblocks;
	off_t		threshold, threshold_sign;
	int		ftsoptions;
	int		depth;
	int		Hflag, Lflag, aflag, sflag, dflag, cflag;
	int		lflag, ch, notused, rval;
	char 		**save;
	static char	dot[] = ".";

	setlocale(LC_ALL, "");

	Hflag = Lflag = aflag = sflag = dflag = cflag = lflag = Aflag = 0;

	save = argv;
	ftsoptions = FTS_PHYSICAL;
	savednumber = 0;
	threshold = 0;
	threshold_sign = 1;
	cblocksize = DEV_BSIZE;
	blocksize = 0;
	depth = INT_MAX;
	SLIST_INIT(&ignores);

	while ((ch = getopt_long(argc, argv, "+AB:HI:LPasd:cghklmnrt:x",
	    long_options, NULL)) != -1)
		switch (ch) {
		case 'A':
			Aflag = 1;
			break;
		case 'B':
			errno = 0;
			cblocksize = atoi(optarg);
			if (errno == ERANGE || cblocksize <= 0) {
				warnx("invalid argument to option B: %s",
				    optarg);
				usage();
			}
			break;
		case 'H':
			Hflag = 1;
			Lflag = 0;
			break;
		case 'I':
			ignoreadd(optarg);
			break;
		case 'L':
			Lflag = 1;
			Hflag = 0;
			break;
		case 'P':
			Hflag = Lflag = 0;
			break;
		case 'a':
			aflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'd':
			dflag = 1;
			errno = 0;
			depth = atoi(optarg);
			if (errno == ERANGE || depth < 0) {
				warnx("invalid argument to option d: %s",
				    optarg);
				usage();
			}
			break;
		case 'c':
			cflag = 1;
			break;
		case 'g':
			hflag = 0;
			blocksize = 1073741824;
			break;
		case 'h':
			hflag = UNITS_2;
			break;
		case 'k':
			hflag = 0;
			blocksize = 1024;
			break;
		case 'l':
			lflag = 1;
			break;
		case 'm':
			hflag = 0;
			blocksize = 1048576;
			break;
		case 'n':
			nodumpflag = 1;
			break;
		case 'r':		 /* Compatibility. */
			break;
		case 't' :
			if (expand_number(optarg, &threshold) != 0 ||
			    threshold == 0) {
				warnx("invalid threshold: %s", optarg);
				usage();
			} else if (threshold < 0)
				threshold_sign = -1;
			break;
		case 'x':
			ftsoptions |= FTS_XDEV;
			break;
		case SI_OPT:
			hflag = UNITS_SI;
			break;
		case '?':
		default:
			usage();
			/* NOTREACHED */
		}

	argc -= optind;
	argv += optind;

	/*
	 * XXX
	 * Because of the way that fts(3) works, logical walks will not count
	 * the blocks actually used by symbolic links.  We rationalize this by
	 * noting that users computing logical sizes are likely to do logical
	 * copies, so not counting the links is correct.  The real reason is
	 * that we'd have to re-implement the kernel's symbolic link traversing
	 * algorithm to get this right.  If, for example, you have relative
	 * symbolic links referencing other relative symbolic links, it gets
	 * very nasty, very fast.  The bottom line is that it's documented in
	 * the man page, so it's a feature.
	 */

	if (Hflag)
		ftsoptions |= FTS_COMFOLLOW;
	if (Lflag) {
		ftsoptions &= ~FTS_PHYSICAL;
		ftsoptions |= FTS_LOGICAL;
	}

	if (!Aflag && (cblocksize % DEV_BSIZE) != 0)
		cblocksize = howmany(cblocksize, DEV_BSIZE) * DEV_BSIZE;

	if (aflag + dflag + sflag > 1)
		usage();
	if (sflag)
		depth = 0;

	if (!*argv) {
		argv = save;
		argv[0] = dot;
		argv[1] = NULL;
	}

	if (blocksize == 0)
		(void)getbsize(&notused, &blocksize);

	if (!Aflag) {
		cblocksize /= DEV_BSIZE;
		blocksize /= DEV_BSIZE;
	}

	if (threshold != 0)
		threshold = howmany(threshold / DEV_BSIZE * cblocksize,
		    blocksize);

	rval = 0;

	(void)signal(SIGINFO, siginfo);

	if ((fts = fts_open(argv, ftsoptions, NULL)) == NULL)
		err(1, "fts_open");

	while ((p = fts_read(fts)) != NULL) {
		switch (p->fts_info) {
		case FTS_D:			/* Ignore. */
			if (ignorep(p))
				fts_set(fts, p, FTS_SKIP);
			break;
		case FTS_DP:
			if (ignorep(p))
				break;

			curblocks = Aflag ?
			    howmany(p->fts_statp->st_size, cblocksize) :
			    howmany(p->fts_statp->st_blocks, cblocksize);
			p->fts_parent->fts_bignum += p->fts_bignum +=
			    curblocks;

			if (p->fts_level <= depth && threshold <=
			    threshold_sign * howmany(p->fts_bignum *
			    cblocksize, blocksize)) {
				if (hflag > 0) {
					prthumanval(p->fts_bignum);
					(void)printf("\t%s\n", p->fts_path);
				} else {
					(void)printf("%jd\t%s\n",
					    (intmax_t)howmany(p->fts_bignum *
					    cblocksize, blocksize),
					    p->fts_path);
				}
			}
			if (info) {
				info = 0;
				(void)printf("\t%s\n", p->fts_path);
			}
			break;
		case FTS_DC:			/* Ignore. */
			break;
		case FTS_DNR:			/* Warn, continue. */
		case FTS_ERR:
		case FTS_NS:
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
			rval = 1;
			break;
		default:
			if (ignorep(p))
				break;

			if (lflag == 0 && p->fts_statp->st_nlink > 1 &&
			    linkchk(p))
				break;

			curblocks = Aflag ?
			    howmany(p->fts_statp->st_size, cblocksize) :
			    howmany(p->fts_statp->st_blocks, cblocksize);

			if (aflag || p->fts_level == 0) {
				if (hflag > 0) {
					prthumanval(curblocks);
					(void)printf("\t%s\n", p->fts_path);
				} else {
					(void)printf("%jd\t%s\n",
					    (intmax_t)howmany(curblocks *
					    cblocksize, blocksize),
					    p->fts_path);
				}
			}

			p->fts_parent->fts_bignum += curblocks;
		}
		savednumber = p->fts_parent->fts_bignum;
	}

	if (errno)
		err(1, "fts_read");

	if (cflag) {
		if (hflag > 0) {
			prthumanval(savednumber);
			(void)printf("\ttotal\n");
		} else {
			(void)printf("%jd\ttotal\n", (intmax_t)howmany(
			    savednumber * cblocksize, blocksize));
		}
	}

	ignoreclean();
	exit(rval);
}