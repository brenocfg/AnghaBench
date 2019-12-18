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
struct label_specs {int dummy; } ;
struct TYPE_5__ {int fts_info; char* fts_path; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
#define  FTS_D 138 
#define  FTS_DC 137 
#define  FTS_DEFAULT 136 
#define  FTS_DNR 135 
#define  FTS_DP 134 
#define  FTS_ERR 133 
#define  FTS_F 132 
 int FTS_LOGICAL ; 
#define  FTS_NS 131 
 int FTS_PHYSICAL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
#define  FTS_SL 130 
#define  FTS_SLNONE 129 
#define  FTS_W 128 
 int FTS_XDEV ; 
 int /*<<< orphan*/  add_setfmac_specs (struct label_specs*,char*) ; 
 int /*<<< orphan*/  add_specs (struct label_specs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  apply_specs (struct label_specs*,TYPE_1__*,int,int) ; 
 char* basename (char*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 struct label_specs* new_specs () ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int qflag ; 
 scalar_t__ specs_empty (struct label_specs*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  usage (int) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
main(int argc, char **argv)
{
	FTSENT *ftsent;
	FTS *fts;
	struct label_specs *specs;
	int eflag = 0, xflag = 0, vflag = 0, Rflag = 0, hflag;
	int ch, is_setfmac;
	char *bn;

	bn = basename(argv[0]);
	if (bn == NULL)
		err(1, "basename");
	is_setfmac = strcmp(bn, "setfmac") == 0;
	hflag = is_setfmac ? FTS_LOGICAL : FTS_PHYSICAL;
	specs = new_specs();
	while ((ch = getopt(argc, argv, is_setfmac ? "Rhq" : "ef:qs:vx")) !=
	    -1) {
		switch (ch) {
		case 'R':
			Rflag = 1;
			break;
		case 'e':
			eflag = 1;
			break;
		case 'f':
			add_specs(specs, optarg, 0);
			break;
		case 'h':
			hflag = FTS_PHYSICAL;
			break;
		case 'q':
			qflag = 1;
			break;
		case 's':
			add_specs(specs, optarg, 1);
			break;
		case 'v':
			vflag++;
			break;
		case 'x':
			xflag = FTS_XDEV;
			break;
		default:
			usage(is_setfmac);
		}
	}
	argc -= optind;
	argv += optind;

	if (is_setfmac) {
		if (argc <= 1)	
			usage(is_setfmac);
		add_setfmac_specs(specs, *argv);
		argc--;
		argv++;
	} else {
		if (argc == 0 || specs_empty(specs))
			usage(is_setfmac);
	}
	fts = fts_open(argv, hflag | xflag, NULL);
	if (fts == NULL)
		err(1, "cannot traverse filesystem%s", argc ? "s" : "");
	while ((ftsent = fts_read(fts)) != NULL) {
		switch (ftsent->fts_info) {
		case FTS_DP:		/* skip post-order */
			break;
		case FTS_D:		/* do pre-order */
		case FTS_DC:		/* do cyclic? */
			/* don't ever recurse directories as setfmac(8) */
			if (is_setfmac && !Rflag)
				fts_set(fts, ftsent, FTS_SKIP);
		case FTS_DEFAULT:	/* do default */
		case FTS_F:		/* do regular */
		case FTS_SL:		/* do symlink */
		case FTS_SLNONE:	/* do symlink */
		case FTS_W:		/* do whiteout */
			if (apply_specs(specs, ftsent, hflag, vflag)) {
				if (eflag) {
					errx(1, "labeling not supported in %s",
					    ftsent->fts_path);
				}
				if (!qflag)
					warnx("labeling not supported in %s",
					    ftsent->fts_path);
				fts_set(fts, ftsent, FTS_SKIP);
			}
			break;
		case FTS_DNR:		/* die on all errors */
		case FTS_ERR:
		case FTS_NS:
			err(1, "traversing %s", ftsent->fts_path);
		default:
			errx(1, "CANNOT HAPPEN (%d) traversing %s",
			    ftsent->fts_info, ftsent->fts_path);
		}
	}
	fts_close(fts);
	exit(0);
}