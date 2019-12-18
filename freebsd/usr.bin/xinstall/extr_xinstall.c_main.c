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
typedef  void* uid_t ;
typedef  scalar_t__ u_long ;
typedef  int u_int ;
struct stat {scalar_t__ st_dev; scalar_t__ st_ino; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  void* id_t ;
typedef  void* gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIGEST_MD5 ; 
 int /*<<< orphan*/  DIGEST_NONE ; 
 int /*<<< orphan*/  DIGEST_RIPEMD160 ; 
 int /*<<< orphan*/  DIGEST_SHA1 ; 
 int /*<<< orphan*/  DIGEST_SHA256 ; 
 int /*<<< orphan*/  DIGEST_SHA512 ; 
 int DIRECTORY ; 
 int /*<<< orphan*/  EFTYPE ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  EX_OK ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 int LN_ABSOLUTE ; 
 int LN_HARD ; 
 int LN_MIXED ; 
 int LN_RELATIVE ; 
 int LN_SYMBOLIC ; 
 int SETFLAGS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 char const* destdir ; 
 char* digest ; 
 int /*<<< orphan*/  digesttype ; 
 int dobackup ; 
 int docompare ; 
 int dodir ; 
 int dolink ; 
 int dopreserve ; 
 int dostrip ; 
 int dounpriv ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char const* fflags ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * getenv (char*) ; 
 int /*<<< orphan*/  getmode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 void* gid ; 
 int gid_from_group (char const*,void**) ; 
 char const* group ; 
 int haveopt_f ; 
 int haveopt_g ; 
 int haveopt_m ; 
 int haveopt_o ; 
 int /*<<< orphan*/  install (char*,char const*,scalar_t__,int) ; 
 int /*<<< orphan*/  install_dir (char*) ; 
 scalar_t__ lstat (char const*,struct stat*) ; 
 char const* metafile ; 
 int /*<<< orphan*/ * metafp ; 
 int /*<<< orphan*/  mode ; 
 char const* optarg ; 
 scalar_t__ optind ; 
 char const* owner ; 
 int /*<<< orphan*/  parseid (char const*,void**) ; 
 int safecopy ; 
 int /*<<< orphan*/ * setmode (char const*) ; 
 int /*<<< orphan*/  setup_getid (char const*) ; 
 int stat (char const*,struct stat*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 scalar_t__ strtofflags (char const**,scalar_t__*,int /*<<< orphan*/ *) ; 
 char const* suffix ; 
 char const* tags ; 
 void* uid ; 
 int uid_from_user (char const*,void**) ; 
 int /*<<< orphan*/  usage () ; 
 int verbose ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	struct stat from_sb, to_sb;
	mode_t *set;
	u_long fset;
	int ch, no_target;
	u_int iflags;
	char *p;
	const char *to_name;

	fset = 0;
	iflags = 0;
	group = owner = NULL;
	while ((ch = getopt(argc, argv, "B:bCcD:df:g:h:l:M:m:N:o:pSsT:Uv")) !=
	     -1)
		switch((char)ch) {
		case 'B':
			suffix = optarg;
			/* FALLTHROUGH */
		case 'b':
			dobackup = 1;
			break;
		case 'C':
			docompare = 1;
			break;
		case 'c':
			/* For backwards compatibility. */
			break;
		case 'D':
			destdir = optarg;
			break;
		case 'd':
			dodir = 1;
			break;
		case 'f':
			haveopt_f = 1;
			fflags = optarg;
			break;
		case 'g':
			haveopt_g = 1;
			group = optarg;
			break;
		case 'h':
			digest = optarg;
			break;
		case 'l':
			for (p = optarg; *p != '\0'; p++)
				switch (*p) {
				case 's':
					dolink &= ~(LN_HARD|LN_MIXED);
					dolink |= LN_SYMBOLIC;
					break;
				case 'h':
					dolink &= ~(LN_SYMBOLIC|LN_MIXED);
					dolink |= LN_HARD;
					break;
				case 'm':
					dolink &= ~(LN_SYMBOLIC|LN_HARD);
					dolink |= LN_MIXED;
					break;
				case 'a':
					dolink &= ~LN_RELATIVE;
					dolink |= LN_ABSOLUTE;
					break;
				case 'r':
					dolink &= ~LN_ABSOLUTE;
					dolink |= LN_RELATIVE;
					break;
				default:
					errx(1, "%c: invalid link type", *p);
					/* NOTREACHED */
				}
			break;
		case 'M':
			metafile = optarg;
			break;
		case 'm':
			haveopt_m = 1;
			if (!(set = setmode(optarg)))
				errx(EX_USAGE, "invalid file mode: %s",
				     optarg);
			mode = getmode(set, 0);
			free(set);
			break;
		case 'N':
			if (!setup_getid(optarg))
				err(EX_OSERR, "Unable to use user and group "
				    "databases in `%s'", optarg);
			break;
		case 'o':
			haveopt_o = 1;
			owner = optarg;
			break;
		case 'p':
			docompare = dopreserve = 1;
			break;
		case 'S':
			safecopy = 1;
			break;
		case 's':
			dostrip = 1;
			break;
		case 'T':
			tags = optarg;
			break;
		case 'U':
			dounpriv = 1;
			break;
		case 'v':
			verbose = 1;
			break;
		case '?':
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	/* some options make no sense when creating directories */
	if (dostrip && dodir) {
		warnx("-d and -s may not be specified together");
		usage();
	}

	if (getenv("DONTSTRIP") != NULL) {
		warnx("DONTSTRIP set - will not strip installed binaries");
		dostrip = 0;
	}

	/* must have at least two arguments, except when creating directories */
	if (argc == 0 || (argc == 1 && !dodir))
		usage();

	if (digest != NULL) {
		if (strcmp(digest, "none") == 0) {
			digesttype = DIGEST_NONE;
		} else if (strcmp(digest, "md5") == 0) {
		       digesttype = DIGEST_MD5;
		} else if (strcmp(digest, "rmd160") == 0) {
			digesttype = DIGEST_RIPEMD160;
		} else if (strcmp(digest, "sha1") == 0) {
			digesttype = DIGEST_SHA1;
		} else if (strcmp(digest, "sha256") == 0) {
			digesttype = DIGEST_SHA256;
		} else if (strcmp(digest, "sha512") == 0) {
			digesttype = DIGEST_SHA512;
		} else {
			warnx("unknown digest `%s'", digest);
			usage();
		}
	}

	/* need to make a temp copy so we can compare stripped version */
	if (docompare && dostrip)
		safecopy = 1;

	/* get group and owner id's */
	if (group != NULL && !dounpriv) {
		if (gid_from_group(group, &gid) == -1) {
			id_t id;
			if (!parseid(group, &id))
				errx(1, "unknown group %s", group);
			gid = id;
		}
	} else
		gid = (gid_t)-1;

	if (owner != NULL && !dounpriv) {
		if (uid_from_user(owner, &uid) == -1) {
			id_t id;
			if (!parseid(owner, &id))
				errx(1, "unknown user %s", owner);
			uid = id;
		}
	} else
		uid = (uid_t)-1;

	if (fflags != NULL && !dounpriv) {
		if (strtofflags(&fflags, &fset, NULL))
			errx(EX_USAGE, "%s: invalid flag", fflags);
		iflags |= SETFLAGS;
	}

	if (metafile != NULL) {
		if ((metafp = fopen(metafile, "a")) == NULL)
			warn("open %s", metafile);
	} else
		digesttype = DIGEST_NONE;

	if (dodir) {
		for (; *argv != NULL; ++argv)
			install_dir(*argv);
		exit(EX_OK);
		/* NOTREACHED */
	}

	to_name = argv[argc - 1];
	no_target = stat(to_name, &to_sb);
	if (!no_target && S_ISDIR(to_sb.st_mode)) {
		if (dolink & LN_SYMBOLIC) {
			if (lstat(to_name, &to_sb) != 0)
				err(EX_OSERR, "%s vanished", to_name);
			if (S_ISLNK(to_sb.st_mode)) {
				if (argc != 2) {
					errno = ENOTDIR;
					err(EX_USAGE, "%s", to_name);
				}
				install(*argv, to_name, fset, iflags);
				exit(EX_OK);
			}
		}
		for (; *argv != to_name; ++argv)
			install(*argv, to_name, fset, iflags | DIRECTORY);
		exit(EX_OK);
		/* NOTREACHED */
	}

	/* can't do file1 file2 directory/file */
	if (argc != 2) {
		if (no_target)
			warnx("target directory `%s' does not exist", 
			    argv[argc - 1]);
		else
			warnx("target `%s' is not a directory",
			    argv[argc - 1]);
		usage();
	}

	if (!no_target && !dolink) {
		if (stat(*argv, &from_sb))
			err(EX_OSERR, "%s", *argv);
		if (!S_ISREG(to_sb.st_mode)) {
			errno = EFTYPE;
			err(EX_OSERR, "%s", to_name);
		}
		if (to_sb.st_dev == from_sb.st_dev &&
		    to_sb.st_ino == from_sb.st_ino)
			errx(EX_USAGE, 
			    "%s and %s are the same file", *argv, to_name);
	}
	install(*argv, to_name, fset, iflags);
	exit(EX_OK);
	/* NOTREACHED */
}