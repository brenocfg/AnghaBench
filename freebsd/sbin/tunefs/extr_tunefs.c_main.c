#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct statfs {char* f_mntonname; int f_flags; } ;
struct iovec {int dummy; } ;
typedef  int /*<<< orphan*/  errmsg ;
struct TYPE_8__ {int fs_flags; int fs_maxbpg; unsigned int fs_avgfilesize; scalar_t__ fs_clean; int fs_metaspace; int fs_fpg; int fs_minfree; size_t fs_optim; unsigned int fs_avgfpdir; scalar_t__ fs_sujfree; int /*<<< orphan*/  fs_volname; } ;
struct TYPE_7__ {char const* d_name; char* d_error; } ;

/* Variables and functions */
 int FS_ACLS ; 
 int FS_DOSOFTDEP ; 
 int FS_GJOURNAL ; 
 int FS_MULTILABEL ; 
 int FS_NFS4ACLS ; 
 size_t FS_OPTSPACE ; 
 size_t FS_OPTTIME ; 
 int FS_SUJ ; 
 int FS_TRIM ; 
 int /*<<< orphan*/  MAXVOLLEN ; 
 int MINFREE ; 
 int MNT_RELOAD ; 
 int MNT_UPDATE ; 
 int /*<<< orphan*/  OPTWARN ; 
 int SUJ_MIN ; 
 int atoi (char*) ; 
 int blknum (TYPE_4__*,int) ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 int /*<<< orphan*/  build_iovec_argf (struct iovec**,int*,char*,char*,...) ; 
 TYPE_1__ disk ; 
 int /*<<< orphan*/  err (int,char*,char const*,...) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 scalar_t__ journal_alloc (int) ; 
 int /*<<< orphan*/  journal_clear () ; 
 scalar_t__ nmount (struct iovec*,int,int) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printfs () ; 
 TYPE_4__ sblock ; 
 int sbwrite (TYPE_1__*,int) ; 
 scalar_t__ statfs (char const*,struct statfs*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ufs_disk_close (TYPE_1__*) ; 
 int ufs_disk_fillout (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*,char const*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int
main(int argc, char *argv[])
{
	const char *avalue, *jvalue, *Jvalue, *Lvalue, *lvalue, *Nvalue, *nvalue;
	const char *tvalue;
	const char *special, *on;
	const char *name;
	int active;
	int Aflag, aflag, eflag, evalue, fflag, fvalue, jflag, Jflag, kflag;
	int kvalue, Lflag, lflag, mflag, mvalue, Nflag, nflag, oflag, ovalue;
	int pflag, sflag, svalue, Svalue, tflag;
	int ch, found_arg, i;
	int iovlen = 0;
	const char *chg[2];
	struct statfs stfs;
	struct iovec *iov = NULL;
	char errmsg[255] = {0};

	if (argc < 3)
		usage();
	Aflag = aflag = eflag = fflag = jflag = Jflag = kflag = Lflag = 0;
	lflag = mflag = Nflag = nflag = oflag = pflag = sflag = tflag = 0;
	avalue = jvalue = Jvalue = Lvalue = lvalue = Nvalue = nvalue = NULL;
	evalue = fvalue = mvalue = ovalue = svalue = Svalue = 0;
	active = 0;
	found_arg = 0;		/* At least one arg is required. */
	while ((ch = getopt(argc, argv, "Aa:e:f:j:J:k:L:l:m:N:n:o:ps:S:t:"))
	    != -1)
		switch (ch) {

		case 'A':
			found_arg = 1;
			Aflag++;
			break;

		case 'a':
			found_arg = 1;
			name = "POSIX.1e ACLs";
			avalue = optarg;
			if (strcmp(avalue, "enable") &&
			    strcmp(avalue, "disable")) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			aflag = 1;
			break;

		case 'e':
			found_arg = 1;
			name = "maximum blocks per file in a cylinder group";
			evalue = atoi(optarg);
			if (evalue < 1)
				errx(10, "%s must be >= 1 (was %s)",
				    name, optarg);
			eflag = 1;
			break;

		case 'f':
			found_arg = 1;
			name = "average file size";
			fvalue = atoi(optarg);
			if (fvalue < 1)
				errx(10, "%s must be >= 1 (was %s)",
				    name, optarg);
			fflag = 1;
			break;

		case 'j':
			found_arg = 1;
			name = "softdep journaled file system";
			jvalue = optarg;
			if (strcmp(jvalue, "enable") &&
			    strcmp(jvalue, "disable")) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			jflag = 1;
			break;

		case 'J':
			found_arg = 1;
			name = "gjournaled file system";
			Jvalue = optarg;
			if (strcmp(Jvalue, "enable") &&
			    strcmp(Jvalue, "disable")) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			Jflag = 1;
			break;

		case 'k':
			found_arg = 1;
			name = "space to hold for metadata blocks";
			kvalue = atoi(optarg);
			if (kvalue < 0)
				errx(10, "bad %s (%s)", name, optarg);
			kflag = 1;
			break;

		case 'L':
			found_arg = 1;
			name = "volume label";
			Lvalue = optarg;
			i = -1;
			while (isalnum(Lvalue[++i]) || Lvalue[i] == '_' ||
			    Lvalue[i] == '-')
				;
			if (Lvalue[i] != '\0') {
				errx(10, "bad %s. Valid characters are "
				    "alphanumerics, dashes, and underscores.",
				    name);
			}
			if (strlen(Lvalue) >= MAXVOLLEN) {
				errx(10, "bad %s. Length is longer than %d.",
				    name, MAXVOLLEN - 1);
			}
			Lflag = 1;
			break;

		case 'l':
			found_arg = 1;
			name = "multilabel MAC file system";
			lvalue = optarg;
			if (strcmp(lvalue, "enable") &&
			    strcmp(lvalue, "disable")) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			lflag = 1;
			break;

		case 'm':
			found_arg = 1;
			name = "minimum percentage of free space";
			mvalue = atoi(optarg);
			if (mvalue < 0 || mvalue > 99)
				errx(10, "bad %s (%s)", name, optarg);
			mflag = 1;
			break;

		case 'N':
			found_arg = 1;
			name = "NFSv4 ACLs";
			Nvalue = optarg;
			if (strcmp(Nvalue, "enable") &&
			    strcmp(Nvalue, "disable")) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			Nflag = 1;
			break;

		case 'n':
			found_arg = 1;
			name = "soft updates";
			nvalue = optarg;
			if (strcmp(nvalue, "enable") != 0 &&
			    strcmp(nvalue, "disable") != 0) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			nflag = 1;
			break;

		case 'o':
			found_arg = 1;
			name = "optimization preference";
			if (strcmp(optarg, "space") == 0)
				ovalue = FS_OPTSPACE;
			else if (strcmp(optarg, "time") == 0)
				ovalue = FS_OPTTIME;
			else
				errx(10,
				    "bad %s (options are `space' or `time')",
				    name);
			oflag = 1;
			break;

		case 'p':
			found_arg = 1;
			pflag = 1;
			break;

		case 's':
			found_arg = 1;
			name = "expected number of files per directory";
			svalue = atoi(optarg);
			if (svalue < 1)
				errx(10, "%s must be >= 1 (was %s)",
				    name, optarg);
			sflag = 1;
			break;

		case 'S':
			found_arg = 1;
			name = "Softdep Journal Size";
			Svalue = atoi(optarg);
			if (Svalue < SUJ_MIN)
				errx(10, "%s must be >= %d (was %s)",
				    name, SUJ_MIN, optarg);
			break;

		case 't':
			found_arg = 1;
			name = "trim";
			tvalue = optarg;
			if (strcmp(tvalue, "enable") != 0 &&
			    strcmp(tvalue, "disable") != 0) {
				errx(10, "bad %s (options are %s)",
				    name, "`enable' or `disable'");
			}
			tflag = 1;
			break;

		default:
			usage();
		}
	argc -= optind;
	argv += optind;
	if (found_arg == 0 || argc != 1)
		usage();

	on = special = argv[0];
	if (ufs_disk_fillout(&disk, special) == -1)
		goto err;
	if (disk.d_name != special) {
		if (statfs(special, &stfs) != 0)
			warn("Can't stat %s", special);
		if (strcmp(special, stfs.f_mntonname) == 0)
			active = 1;
	}

	if (pflag) {
		printfs();
		exit(0);
	}
	if (Lflag) {
		name = "volume label";
		strncpy(sblock.fs_volname, Lvalue, MAXVOLLEN);
	}
	if (aflag) {
		name = "POSIX.1e ACLs";
		if (strcmp(avalue, "enable") == 0) {
			if (sblock.fs_flags & FS_ACLS) {
				warnx("%s remains unchanged as enabled", name);
			} else if (sblock.fs_flags & FS_NFS4ACLS) {
				warnx("%s and NFSv4 ACLs are mutually "
				    "exclusive", name);
			} else {
				sblock.fs_flags |= FS_ACLS;
				warnx("%s set", name);
			}
		} else if (strcmp(avalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_ACLS) ==
			    FS_ACLS) {
				warnx("%s remains unchanged as disabled",
				    name);
			} else {
				sblock.fs_flags &= ~FS_ACLS;
				warnx("%s cleared", name);
			}
		}
	}
	if (eflag) {
		name = "maximum blocks per file in a cylinder group";
		if (sblock.fs_maxbpg == evalue)
			warnx("%s remains unchanged as %d", name, evalue);
		else {
			warnx("%s changes from %d to %d",
			    name, sblock.fs_maxbpg, evalue);
			sblock.fs_maxbpg = evalue;
		}
	}
	if (fflag) {
		name = "average file size";
		if (sblock.fs_avgfilesize == (unsigned)fvalue) {
			warnx("%s remains unchanged as %d", name, fvalue);
		}
		else {
			warnx("%s changes from %d to %d",
					name, sblock.fs_avgfilesize, fvalue);
			sblock.fs_avgfilesize = fvalue;
		}
	}
	if (jflag) {
 		name = "soft updates journaling";
 		if (strcmp(jvalue, "enable") == 0) {
			if ((sblock.fs_flags & (FS_DOSOFTDEP | FS_SUJ)) ==
			    (FS_DOSOFTDEP | FS_SUJ)) {
				warnx("%s remains unchanged as enabled", name);
			} else if (sblock.fs_clean == 0) {
				warnx("%s cannot be enabled until fsck is run",
				    name);
			} else if (journal_alloc(Svalue) != 0) {
				warnx("%s cannot be enabled", name);
			} else {
 				sblock.fs_flags |= FS_DOSOFTDEP | FS_SUJ;
 				warnx("%s set", name);
			}
 		} else if (strcmp(jvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_SUJ) == FS_SUJ) {
				warnx("%s remains unchanged as disabled", name);
			} else {
				journal_clear();
 				sblock.fs_flags &= ~FS_SUJ;
				sblock.fs_sujfree = 0;
 				warnx("%s cleared but soft updates still set.",
				    name);

				warnx("remove .sujournal to reclaim space");
			}
 		}
	}
	if (Jflag) {
		name = "gjournal";
		if (strcmp(Jvalue, "enable") == 0) {
			if (sblock.fs_flags & FS_GJOURNAL) {
				warnx("%s remains unchanged as enabled", name);
			} else {
				sblock.fs_flags |= FS_GJOURNAL;
				warnx("%s set", name);
			}
		} else if (strcmp(Jvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_GJOURNAL) ==
			    FS_GJOURNAL) {
				warnx("%s remains unchanged as disabled",
				    name);
			} else {
				sblock.fs_flags &= ~FS_GJOURNAL;
				warnx("%s cleared", name);
			}
		}
	}
	if (kflag) {
		name = "space to hold for metadata blocks";
		if (sblock.fs_metaspace == kvalue)
			warnx("%s remains unchanged as %d", name, kvalue);
		else {
			kvalue = blknum(&sblock, kvalue);
			if (kvalue > sblock.fs_fpg / 2) {
				kvalue = blknum(&sblock, sblock.fs_fpg / 2);
				warnx("%s cannot exceed half the file system "
				    "space", name);
			}
			warnx("%s changes from %jd to %d",
				    name, sblock.fs_metaspace, kvalue);
			sblock.fs_metaspace = kvalue;
		}
	}
	if (lflag) {
		name = "multilabel";
		if (strcmp(lvalue, "enable") == 0) {
			if (sblock.fs_flags & FS_MULTILABEL) {
				warnx("%s remains unchanged as enabled", name);
			} else {
				sblock.fs_flags |= FS_MULTILABEL;
				warnx("%s set", name);
			}
		} else if (strcmp(lvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_MULTILABEL) ==
			    FS_MULTILABEL) {
				warnx("%s remains unchanged as disabled",
				    name);
			} else {
				sblock.fs_flags &= ~FS_MULTILABEL;
				warnx("%s cleared", name);
			}
		}
	}
	if (mflag) {
		name = "minimum percentage of free space";
		if (sblock.fs_minfree == mvalue)
			warnx("%s remains unchanged as %d%%", name, mvalue);
		else {
			warnx("%s changes from %d%% to %d%%",
				    name, sblock.fs_minfree, mvalue);
			sblock.fs_minfree = mvalue;
			if (mvalue >= MINFREE && sblock.fs_optim == FS_OPTSPACE)
				warnx(OPTWARN, "time", ">=", MINFREE);
			if (mvalue < MINFREE && sblock.fs_optim == FS_OPTTIME)
				warnx(OPTWARN, "space", "<", MINFREE);
		}
	}
	if (Nflag) {
		name = "NFSv4 ACLs";
		if (strcmp(Nvalue, "enable") == 0) {
			if (sblock.fs_flags & FS_NFS4ACLS) {
				warnx("%s remains unchanged as enabled", name);
			} else if (sblock.fs_flags & FS_ACLS) {
				warnx("%s and POSIX.1e ACLs are mutually "
				    "exclusive", name);
			} else {
				sblock.fs_flags |= FS_NFS4ACLS;
				warnx("%s set", name);
			}
		} else if (strcmp(Nvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_NFS4ACLS) ==
			    FS_NFS4ACLS) {
				warnx("%s remains unchanged as disabled",
				    name);
			} else {
				sblock.fs_flags &= ~FS_NFS4ACLS;
				warnx("%s cleared", name);
			}
		}
	}
	if (nflag) {
 		name = "soft updates";
 		if (strcmp(nvalue, "enable") == 0) {
			if (sblock.fs_flags & FS_DOSOFTDEP)
				warnx("%s remains unchanged as enabled", name);
			else if (sblock.fs_clean == 0) {
				warnx("%s cannot be enabled until fsck is run",
				    name);
			} else {
 				sblock.fs_flags |= FS_DOSOFTDEP;
 				warnx("%s set", name);
			}
 		} else if (strcmp(nvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_DOSOFTDEP) == FS_DOSOFTDEP)
				warnx("%s remains unchanged as disabled", name);
			else {
 				sblock.fs_flags &= ~FS_DOSOFTDEP;
 				warnx("%s cleared", name);
			}
 		}
	}
	if (oflag) {
		name = "optimization preference";
		chg[FS_OPTSPACE] = "space";
		chg[FS_OPTTIME] = "time";
		if (sblock.fs_optim == ovalue)
			warnx("%s remains unchanged as %s", name, chg[ovalue]);
		else {
			warnx("%s changes from %s to %s",
				    name, chg[sblock.fs_optim], chg[ovalue]);
			sblock.fs_optim = ovalue;
			if (sblock.fs_minfree >= MINFREE &&
			    ovalue == FS_OPTSPACE)
				warnx(OPTWARN, "time", ">=", MINFREE);
			if (sblock.fs_minfree < MINFREE && ovalue == FS_OPTTIME)
				warnx(OPTWARN, "space", "<", MINFREE);
		}
	}
	if (sflag) {
		name = "expected number of files per directory";
		if (sblock.fs_avgfpdir == (unsigned)svalue) {
			warnx("%s remains unchanged as %d", name, svalue);
		}
		else {
			warnx("%s changes from %d to %d",
					name, sblock.fs_avgfpdir, svalue);
			sblock.fs_avgfpdir = svalue;
		}
	}
	if (tflag) {
		name = "issue TRIM to the disk";
 		if (strcmp(tvalue, "enable") == 0) {
			if (sblock.fs_flags & FS_TRIM)
				warnx("%s remains unchanged as enabled", name);
			else {
 				sblock.fs_flags |= FS_TRIM;
 				warnx("%s set", name);
			}
 		} else if (strcmp(tvalue, "disable") == 0) {
			if ((~sblock.fs_flags & FS_TRIM) == FS_TRIM)
				warnx("%s remains unchanged as disabled", name);
			else {
 				sblock.fs_flags &= ~FS_TRIM;
 				warnx("%s cleared", name);
			}
 		}
	}

	if (sbwrite(&disk, Aflag) == -1)
		goto err;
	ufs_disk_close(&disk);
	if (active) {
		build_iovec_argf(&iov, &iovlen, "fstype", "ufs");
		build_iovec_argf(&iov, &iovlen, "fspath", "%s", on);
		build_iovec(&iov, &iovlen, "errmsg", errmsg, sizeof(errmsg));
		if (nmount(iov, iovlen,
		    stfs.f_flags | MNT_UPDATE | MNT_RELOAD) < 0) {
			if (errmsg[0])
				err(9, "%s: reload: %s", special, errmsg);
			else
				err(9, "%s: reload", special);
		}
		warnx("file system reloaded");
	}
	exit(0);
err:
	if (disk.d_error != NULL)
		errx(11, "%s: %s", special, disk.d_error);
	else
		err(12, "%s", special);
}