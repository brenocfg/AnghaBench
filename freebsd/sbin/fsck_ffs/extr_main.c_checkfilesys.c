#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  long uintmax_t ;
typedef  double ufs2_daddr_t ;
struct statfs {char* f_mntfromname; int f_flags; char* f_mntonname; } ;
struct stat {int /*<<< orphan*/  st_mode; } ;
struct iovec {int dummy; } ;
struct group {int /*<<< orphan*/  gr_gid; } ;
struct dups {scalar_t__ dup; struct dups* next; } ;
typedef  long intmax_t ;
typedef  int /*<<< orphan*/  errmsg ;
struct TYPE_13__ {int /*<<< orphan*/ * il_stat; } ;
struct TYPE_12__ {scalar_t__ b_dirty; } ;
struct TYPE_10__ {int cs_nffree; int cs_nbfree; long cs_nifree; long cs_ndir; } ;
struct TYPE_11__ {int fs_flags; int fs_clean; int fs_frag; double fs_dsize; int fs_metackhash; scalar_t__ fs_magic; char* fs_fsmnt; int fs_ncg; void* fs_time; TYPE_1__ fs_cstotal; int /*<<< orphan*/  fs_fsize; int /*<<< orphan*/  fs_cssize; void* fs_mtime; } ;

/* Variables and functions */
 int CK_CYLGRP ; 
 int CK_DIR ; 
 int CK_INDIR ; 
 int CK_INODE ; 
 int CK_SUPERBLOCK ; 
 int /*<<< orphan*/  CLOCK_REALTIME_PRECISE ; 
 scalar_t__ EEXIST ; 
 scalar_t__ ENOENT ; 
 int ERERUN ; 
 int ERESTART ; 
 int FS_DOSOFTDEP ; 
 int FS_GJOURNAL ; 
 int FS_METACKHASH ; 
 int FS_NEEDSFSCK ; 
 int FS_SUJ ; 
 scalar_t__ FS_UFS1_MAGIC ; 
 int FS_UNCLEAN ; 
 int /*<<< orphan*/  IOstats (char*) ; 
 size_t MIBSIZE ; 
 int MNT_RDONLY ; 
 int MNT_ROOTFS ; 
 int MNT_SOFTDEP ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ P_OSREL_CK_CYLGRP ; 
 scalar_t__ P_OSREL_CK_DIR ; 
 scalar_t__ P_OSREL_CK_INDIR ; 
 scalar_t__ P_OSREL_CK_INODE ; 
 scalar_t__ P_OSREL_CK_SUPERBLOCK ; 
 int /*<<< orphan*/  SBLOCKSIZE ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 long UFS_ROOTINO ; 
 int /*<<< orphan*/  adjrefcnt ; 
 scalar_t__ bkgrdcheck ; 
 scalar_t__ bkgrdflag ; 
 char* blockcheck (char*) ; 
 int /*<<< orphan*/  blwrite (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_iovec (struct iovec**,int*,char*,char*,int) ; 
 char* cdevname ; 
 int cgbase (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int cgdmin (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int cgsblock (TYPE_2__*,int) ; 
 scalar_t__ chkdoreload (struct statfs*) ; 
 scalar_t__ chmod (char*,int) ; 
 scalar_t__ chown (char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ckclean ; 
 int /*<<< orphan*/  ckfini (int) ; 
 int ckhashadd ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 long countdirs ; 
 scalar_t__ cvtlevel ; 
 scalar_t__ debug ; 
 struct dups* duplist ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  finalIOstats () ; 
 int /*<<< orphan*/  flush (int,TYPE_3__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fsbtodb (TYPE_2__*,int) ; 
 int /*<<< orphan*/  fsckinit () ; 
 int fsmodified ; 
 int /*<<< orphan*/  fsreadfd ; 
 int /*<<< orphan*/  fsutilinit () ; 
 int fswritefd ; 
 struct group* getgrnam (char*) ; 
 struct statfs* getmntpt (char*) ; 
 scalar_t__ getosreldate () ; 
 int /*<<< orphan*/  gjournal_check (char*) ; 
 scalar_t__ howmany (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inocleanup () ; 
 TYPE_4__* inostathead ; 
 double maxfsblock ; 
 long maxino ; 
 scalar_t__ mkdir (char*,int) ; 
 struct dups* muldup ; 
 long n_blks ; 
 long n_files ; 
 scalar_t__ nmount (struct iovec*,int,int) ; 
 int /*<<< orphan*/  open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pass1 () ; 
 int /*<<< orphan*/  pass1b () ; 
 int /*<<< orphan*/  pass2 () ; 
 int /*<<< orphan*/  pass3 () ; 
 int /*<<< orphan*/  pass4 () ; 
 int /*<<< orphan*/  pass5 () ; 
 int /*<<< orphan*/  pfatal (char*,...) ; 
 scalar_t__ preen ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  pwarn (char*,...) ; 
 scalar_t__ readsb (int /*<<< orphan*/ ) ; 
 scalar_t__ reply (char*) ; 
 scalar_t__ rerun ; 
 int resolved ; 
 int /*<<< orphan*/  restarts ; 
 int /*<<< orphan*/  sbdirty () ; 
 TYPE_3__ sblk ; 
 TYPE_2__ sblock ; 
 int /*<<< orphan*/  sblock_init () ; 
 int setup (char*) ; 
 scalar_t__ skipclean ; 
 char* snapname ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  startprog ; 
 scalar_t__ stat (char*,struct stat*) ; 
 char* strerror (scalar_t__) ; 
 scalar_t__ suj_check (char*) ; 
 int /*<<< orphan*/  sync () ; 
 scalar_t__ sysctlnametomib (char*,int /*<<< orphan*/ ,size_t*) ; 
 void* time (int /*<<< orphan*/ *) ; 
 scalar_t__ unlink (char*) ; 
 scalar_t__ usedsoftdep ; 
 scalar_t__ wantrestart ; 
 scalar_t__ yflag ; 

__attribute__((used)) static int
checkfilesys(char *filesys)
{
	ufs2_daddr_t n_ffree, n_bfree;
	struct dups *dp;
	struct statfs *mntp;
	struct stat snapdir;
	struct group *grp;
	struct iovec *iov;
	char errmsg[255];
	int ofsmodified;
	int iovlen;
	int cylno;
	intmax_t blks, files;
	size_t size;

	iov = NULL;
	iovlen = 0;
	errmsg[0] = '\0';
	fsutilinit();
	fsckinit();

	cdevname = filesys;
	if (debug && ckclean)
		pwarn("starting\n");
	/*
	 * Make best effort to get the disk name. Check first to see
	 * if it is listed among the mounted file systems. Failing that
	 * check to see if it is listed in /etc/fstab.
	 */
	mntp = getmntpt(filesys);
	if (mntp != NULL)
		filesys = mntp->f_mntfromname;
	else
		filesys = blockcheck(filesys);
	/*
	 * If -F flag specified, check to see whether a background check
	 * is possible and needed. If possible and needed, exit with
	 * status zero. Otherwise exit with status non-zero. A non-zero
	 * exit status will cause a foreground check to be run.
	 */
	sblock_init();
	if (bkgrdcheck) {
		if ((fsreadfd = open(filesys, O_RDONLY)) < 0 || readsb(0) == 0)
			exit(3);	/* Cannot read superblock */
		close(fsreadfd);
		/* Earlier background failed or journaled */
		if (sblock.fs_flags & (FS_NEEDSFSCK | FS_SUJ))
			exit(4);
		if ((sblock.fs_flags & FS_DOSOFTDEP) == 0)
			exit(5);	/* Not running soft updates */
		size = MIBSIZE;
		if (sysctlnametomib("vfs.ffs.adjrefcnt", adjrefcnt, &size) < 0)
			exit(6);	/* Lacks kernel support */
		if ((mntp == NULL && sblock.fs_clean == 1) ||
		    (mntp != NULL && (sblock.fs_flags & FS_UNCLEAN) == 0))
			exit(7);	/* Filesystem clean, report it now */
		exit(0);
	}
	if (ckclean && skipclean) {
		/*
		 * If file system is gjournaled, check it here.
		 */
		if ((fsreadfd = open(filesys, O_RDONLY)) < 0 || readsb(0) == 0)
			exit(3);	/* Cannot read superblock */
		close(fsreadfd);
		if ((sblock.fs_flags & FS_GJOURNAL) != 0) {
			//printf("GJournaled file system detected on %s.\n",
			//    filesys);
			if (sblock.fs_clean == 1) {
				pwarn("FILE SYSTEM CLEAN; SKIPPING CHECKS\n");
				exit(0);
			}
			if ((sblock.fs_flags & (FS_UNCLEAN | FS_NEEDSFSCK)) == 0) {
				gjournal_check(filesys);
				if (chkdoreload(mntp) == 0)
					exit(0);
				exit(4);
			} else {
				pfatal(
			    "UNEXPECTED INCONSISTENCY, CANNOT RUN FAST FSCK\n");
			}
		}
	}
	/*
	 * If we are to do a background check:
	 *	Get the mount point information of the file system
	 *	create snapshot file
	 *	return created snapshot file
	 *	if not found, clear bkgrdflag and proceed with normal fsck
	 */
	if (bkgrdflag) {
		if (mntp == NULL) {
			bkgrdflag = 0;
			pfatal("NOT MOUNTED, CANNOT RUN IN BACKGROUND\n");
		} else if ((mntp->f_flags & MNT_SOFTDEP) == 0) {
			bkgrdflag = 0;
			pfatal(
			  "NOT USING SOFT UPDATES, CANNOT RUN IN BACKGROUND\n");
		} else if ((mntp->f_flags & MNT_RDONLY) != 0) {
			bkgrdflag = 0;
			pfatal("MOUNTED READ-ONLY, CANNOT RUN IN BACKGROUND\n");
		} else if ((fsreadfd = open(filesys, O_RDONLY)) >= 0) {
			if (readsb(0) != 0) {
				if (sblock.fs_flags & (FS_NEEDSFSCK | FS_SUJ)) {
					bkgrdflag = 0;
					pfatal(
			"UNEXPECTED INCONSISTENCY, CANNOT RUN IN BACKGROUND\n");
				}
				if ((sblock.fs_flags & FS_UNCLEAN) == 0 &&
				    skipclean && ckclean) {
					/*
					 * file system is clean;
					 * skip snapshot and report it clean
					 */
					pwarn(
					"FILE SYSTEM CLEAN; SKIPPING CHECKS\n");
					goto clean;
				}
			}
			close(fsreadfd);
		}
		if (bkgrdflag) {
			snprintf(snapname, sizeof snapname, "%s/.snap",
			    mntp->f_mntonname);
			if (stat(snapname, &snapdir) < 0) {
				if (errno != ENOENT) {
					bkgrdflag = 0;
					pfatal(
	"CANNOT FIND SNAPSHOT DIRECTORY %s: %s, CANNOT RUN IN BACKGROUND\n",
					    snapname, strerror(errno));
				} else if ((grp = getgrnam("operator")) == NULL ||
					   mkdir(snapname, 0770) < 0 ||
					   chown(snapname, -1, grp->gr_gid) < 0 ||
					   chmod(snapname, 0770) < 0) {
					bkgrdflag = 0;
					pfatal(
	"CANNOT CREATE SNAPSHOT DIRECTORY %s: %s, CANNOT RUN IN BACKGROUND\n",
					    snapname, strerror(errno));
				}
			} else if (!S_ISDIR(snapdir.st_mode)) {
				bkgrdflag = 0;
				pfatal(
			"%s IS NOT A DIRECTORY, CANNOT RUN IN BACKGROUND\n",
				    snapname);
			}
		}
		if (bkgrdflag) {
			snprintf(snapname, sizeof snapname,
			    "%s/.snap/fsck_snapshot", mntp->f_mntonname);
			build_iovec(&iov, &iovlen, "fstype", "ffs", 4);
			build_iovec(&iov, &iovlen, "from", snapname,
			    (size_t)-1);
			build_iovec(&iov, &iovlen, "fspath", mntp->f_mntonname,
			    (size_t)-1);
			build_iovec(&iov, &iovlen, "errmsg", errmsg,
			    sizeof(errmsg));
			build_iovec(&iov, &iovlen, "update", NULL, 0);
			build_iovec(&iov, &iovlen, "snapshot", NULL, 0);

			while (nmount(iov, iovlen, mntp->f_flags) < 0) {
				if (errno == EEXIST && unlink(snapname) == 0)
					continue;
				bkgrdflag = 0;
				pfatal("CANNOT CREATE SNAPSHOT %s: %s %s\n",
				    snapname, strerror(errno), errmsg);
				break;
			}
			if (bkgrdflag != 0)
				filesys = snapname;
		}
	}

	switch (setup(filesys)) {
	case 0:
		if (preen)
			pfatal("CAN'T CHECK FILE SYSTEM.");
		return (0);
	case -1:
	clean:
		pwarn("clean, %ld free ", (long)(sblock.fs_cstotal.cs_nffree +
		    sblock.fs_frag * sblock.fs_cstotal.cs_nbfree));
		printf("(%jd frags, %jd blocks, %.1f%% fragmentation)\n",
		    (intmax_t)sblock.fs_cstotal.cs_nffree,
		    (intmax_t)sblock.fs_cstotal.cs_nbfree,
		    sblock.fs_cstotal.cs_nffree * 100.0 / sblock.fs_dsize);
		return (0);
	}
	/*
	 * Determine if we can and should do journal recovery.
	 */
	if ((sblock.fs_flags & FS_SUJ) == FS_SUJ) {
		if ((sblock.fs_flags & FS_NEEDSFSCK) != FS_NEEDSFSCK && skipclean) {
			if (preen || reply("USE JOURNAL")) {
				if (suj_check(filesys) == 0) {
					printf("\n***** FILE SYSTEM MARKED CLEAN *****\n");
					if (chkdoreload(mntp) == 0)
						exit(0);
					exit(4);
				}
			}
			printf("** Skipping journal, falling through to full fsck\n\n");
		}
		/*
		 * Write the superblock so we don't try to recover the
		 * journal on another pass. If this is the only change
		 * to the filesystem, we do not want it to be called
		 * out as modified.
		 */
		sblock.fs_mtime = time(NULL);
		sbdirty();
		ofsmodified = fsmodified;
		flush(fswritefd, &sblk);
		fsmodified = ofsmodified;
	}
	/*
	 * If the filesystem was run on an old kernel that did not
	 * support check hashes, clear the check-hash flags so that
	 * we do not try to verify them.
	 */
	if ((sblock.fs_flags & FS_METACKHASH) == 0)
		sblock.fs_metackhash = 0;
	/*
	 * If we are running on a kernel that can provide check hashes
	 * that are not yet enabled for the filesystem and we are
	 * running manually without the -y flag, offer to add any
	 * supported check hashes that are not already enabled.
	 */
	ckhashadd = 0;
	if (preen == 0 && yflag == 0 && sblock.fs_magic != FS_UFS1_MAGIC &&
	    fswritefd != -1 && getosreldate() >= P_OSREL_CK_CYLGRP) {
		if ((sblock.fs_metackhash & CK_CYLGRP) == 0 &&
		    reply("ADD CYLINDER GROUP CHECK-HASH PROTECTION") != 0) {
			ckhashadd |= CK_CYLGRP;
			sblock.fs_metackhash |= CK_CYLGRP;
		}
		if ((sblock.fs_metackhash & CK_SUPERBLOCK) == 0 &&
		    getosreldate() >= P_OSREL_CK_SUPERBLOCK &&
		    reply("ADD SUPERBLOCK CHECK-HASH PROTECTION") != 0) {
			ckhashadd |= CK_SUPERBLOCK;
			sblock.fs_metackhash |= CK_SUPERBLOCK;
		}
		if ((sblock.fs_metackhash & CK_INODE) == 0 &&
		    getosreldate() >= P_OSREL_CK_INODE &&
		    reply("ADD INODE CHECK-HASH PROTECTION") != 0) {
			ckhashadd |= CK_INODE;
			sblock.fs_metackhash |= CK_INODE;
		}
#ifdef notyet
		if ((sblock.fs_metackhash & CK_INDIR) == 0 &&
		    getosreldate() >= P_OSREL_CK_INDIR &&
		    reply("ADD INDIRECT BLOCK CHECK-HASH PROTECTION") != 0) {
			ckhashadd |= CK_INDIR;
			sblock.fs_metackhash |= CK_INDIR;
		}
		if ((sblock.fs_metackhash & CK_DIR) == 0 &&
		    getosreldate() >= P_OSREL_CK_DIR &&
		    reply("ADD DIRECTORY CHECK-HASH PROTECTION") != 0) {
			ckhashadd |= CK_DIR;
			sblock.fs_metackhash |= CK_DIR;
		}
#endif /* notyet */
		if (ckhashadd != 0) {
			sblock.fs_flags |= FS_METACKHASH;
			sbdirty();
		}
	}
	/*
	 * Cleared if any questions answered no. Used to decide if
	 * the superblock should be marked clean.
	 */
	resolved = 1;
	/*
	 * 1: scan inodes tallying blocks used
	 */
	if (preen == 0) {
		printf("** Last Mounted on %s\n", sblock.fs_fsmnt);
		if (mntp != NULL && mntp->f_flags & MNT_ROOTFS)
			printf("** Root file system\n");
		printf("** Phase 1 - Check Blocks and Sizes\n");
	}
	clock_gettime(CLOCK_REALTIME_PRECISE, &startprog);
	pass1();
	IOstats("Pass1");

	/*
	 * 1b: locate first references to duplicates, if any
	 */
	if (duplist) {
		if (preen || usedsoftdep)
			pfatal("INTERNAL ERROR: dups with %s%s%s",
			    preen ? "-p" : "",
			    (preen && usedsoftdep) ? " and " : "",
			    usedsoftdep ? "softupdates" : "");
		printf("** Phase 1b - Rescan For More DUPS\n");
		pass1b();
		IOstats("Pass1b");
	}

	/*
	 * 2: traverse directories from root to mark all connected directories
	 */
	if (preen == 0)
		printf("** Phase 2 - Check Pathnames\n");
	pass2();
	IOstats("Pass2");

	/*
	 * 3: scan inodes looking for disconnected directories
	 */
	if (preen == 0)
		printf("** Phase 3 - Check Connectivity\n");
	pass3();
	IOstats("Pass3");

	/*
	 * 4: scan inodes looking for disconnected files; check reference counts
	 */
	if (preen == 0)
		printf("** Phase 4 - Check Reference Counts\n");
	pass4();
	IOstats("Pass4");

	/*
	 * 5: check and repair resource counts in cylinder groups
	 */
	if (preen == 0)
		printf("** Phase 5 - Check Cyl groups\n");
	pass5();
	IOstats("Pass5");

	/*
	 * print out summary statistics
	 */
	n_ffree = sblock.fs_cstotal.cs_nffree;
	n_bfree = sblock.fs_cstotal.cs_nbfree;
	files = maxino - UFS_ROOTINO - sblock.fs_cstotal.cs_nifree - n_files;
	blks = n_blks +
	    sblock.fs_ncg * (cgdmin(&sblock, 0) - cgsblock(&sblock, 0));
	blks += cgsblock(&sblock, 0) - cgbase(&sblock, 0);
	blks += howmany(sblock.fs_cssize, sblock.fs_fsize);
	blks = maxfsblock - (n_ffree + sblock.fs_frag * n_bfree) - blks;
	if (bkgrdflag && (files > 0 || blks > 0)) {
		countdirs = sblock.fs_cstotal.cs_ndir - countdirs;
		pwarn("Reclaimed: %ld directories, %jd files, %jd fragments\n",
		    countdirs, files - countdirs, blks);
	}
	pwarn("%ld files, %jd used, %ju free ",
	    (long)n_files, (intmax_t)n_blks,
	    (uintmax_t)n_ffree + sblock.fs_frag * n_bfree);
	printf("(%ju frags, %ju blocks, %.1f%% fragmentation)\n",
	    (uintmax_t)n_ffree, (uintmax_t)n_bfree,
	    n_ffree * 100.0 / sblock.fs_dsize);
	if (debug) {
		if (files < 0)
			printf("%jd inodes missing\n", -files);
		if (blks < 0)
			printf("%jd blocks missing\n", -blks);
		if (duplist != NULL) {
			printf("The following duplicate blocks remain:");
			for (dp = duplist; dp; dp = dp->next)
				printf(" %jd,", (intmax_t)dp->dup);
			printf("\n");
		}
	}
	duplist = (struct dups *)0;
	muldup = (struct dups *)0;
	inocleanup();
	if (fsmodified) {
		sblock.fs_time = time(NULL);
		sbdirty();
	}
	if (cvtlevel && sblk.b_dirty) {
		/*
		 * Write out the duplicate super blocks
		 */
		for (cylno = 0; cylno < sblock.fs_ncg; cylno++)
			blwrite(fswritefd, (char *)&sblock,
			    fsbtodb(&sblock, cgsblock(&sblock, cylno)),
			    SBLOCKSIZE);
	}
	if (rerun)
		resolved = 0;
	finalIOstats();

	/*
	 * Check to see if the file system is mounted read-write.
	 */
	if (bkgrdflag == 0 && mntp != NULL && (mntp->f_flags & MNT_RDONLY) == 0)
		resolved = 0;
	ckfini(resolved);

	for (cylno = 0; cylno < sblock.fs_ncg; cylno++)
		if (inostathead[cylno].il_stat != NULL)
			free((char *)inostathead[cylno].il_stat);
	free((char *)inostathead);
	inostathead = NULL;
	if (fsmodified && !preen)
		printf("\n***** FILE SYSTEM WAS MODIFIED *****\n");
	if (rerun) {
		if (wantrestart && (restarts++ < 10) &&
		    (preen || reply("RESTART")))
			return (ERESTART);
		printf("\n***** PLEASE RERUN FSCK *****\n");
	}
	if (chkdoreload(mntp) != 0) {
		if (!fsmodified)
			return (0);
		if (!preen)
			printf("\n***** REBOOT NOW *****\n");
		sync();
		return (4);
	}
	return (rerun ? ERERUN : 0);
}