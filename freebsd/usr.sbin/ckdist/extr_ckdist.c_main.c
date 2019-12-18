#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {int fts_info; char* fts_path; size_t fts_errno; int /*<<< orphan*/  fts_name; int /*<<< orphan*/  fts_level; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
#define  FTS_D 133 
#define  FTS_DC 132 
#define  FTS_DNR 131 
#define  FTS_ERR 130 
#define  FTS_F 129 
 int /*<<< orphan*/  FTS_LOGICAL ; 
#define  FTS_NS 128 
 int /*<<< orphan*/  FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int ckdist (char*,int) ; 
 int distfile (int /*<<< orphan*/ ) ; 
 int disttype (void*) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 int fail (char*,char*) ; 
 scalar_t__ fts_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fts_open (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ isstdin (char*) ; 
 int opt_all ; 
 char* opt_dir ; 
 int opt_exist ; 
 int opt_ignore ; 
 void* opt_name ; 
 int opt_recurse ; 
 int opt_silent ; 
 int opt_type ; 
 void* optarg ; 
 scalar_t__ optind ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char** sys_errlist ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
    static char *arg[2];
    struct stat sb;
    FTS *ftsp;
    FTSENT *f;
    int rval, c, type;

    while ((c = getopt(argc, argv, "ad:in:rst:x")) != -1)
	switch (c) {
	case 'a':
	    opt_all = 1;
	    break;
	case 'd':
	    opt_dir = optarg;
	    break;
	case 'i':
	    opt_ignore = 1;
	    break;
	case 'n':
	    opt_name = optarg;
	    break;
	case 'r':
	    opt_recurse = 1;
	    break;
	case 's':
	    opt_silent = 1;
	    break;
	case 't':
	    if ((opt_type = disttype(optarg)) == 0) {
		warnx("illegal argument to -t option");
		usage();
	    }
	    break;
	case 'x':
	    opt_exist = 1;
	    break;
	default:
	    usage();
	}
    argc -= optind;
    argv += optind;
    if (argc < 1)
	usage();
    if (opt_dir) {
	if (stat(opt_dir, &sb))
	    err(2, "%s", opt_dir);
	if (!S_ISDIR(sb.st_mode))
	    errx(2, "%s: not a directory", opt_dir);
    }
    rval = 0;
    do {
	if (isstdin(*argv))
	    rval |= ckdist(*argv, opt_type);
	else if (stat(*argv, &sb))
	    rval |= fail(*argv, NULL);
	else if (S_ISREG(sb.st_mode))
	    rval |= ckdist(*argv, opt_type);
	else {
	    arg[0] = *argv;
	    if ((ftsp = fts_open(arg, FTS_LOGICAL, NULL)) == NULL)
		err(2, "fts_open");
	    while ((f = fts_read(ftsp)) != NULL)
		switch (f->fts_info) {
		case FTS_DC:
		    rval = fail(f->fts_path, "Directory causes a cycle");
		    break;
		case FTS_DNR:
		case FTS_ERR:
		case FTS_NS:
		    rval = fail(f->fts_path, sys_errlist[f->fts_errno]);
		    break;
		case FTS_D:
		    if (!opt_recurse && f->fts_level > FTS_ROOTLEVEL &&
			fts_set(ftsp, f, FTS_SKIP))
			err(2, "fts_set");
		    break;
		case FTS_F:
		    if ((type = distfile(f->fts_name)) != 0 &&
			(!opt_type || type == opt_type))
			rval |= ckdist(f->fts_path, type);
		    break;
                default: ;
		}
	    if (errno)
		err(2, "fts_read");
	    if (fts_close(ftsp))
		err(2, "fts_close");
	}
    } while (*++argv);
    return rval;
}