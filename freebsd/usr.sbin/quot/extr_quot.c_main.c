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
struct statfs {char* f_mntfromname; int /*<<< orphan*/  f_mntonname; int /*<<< orphan*/  f_fstypename; } ;
struct fstab {char* fs_spec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MFSNAMELEN ; 
 int /*<<< orphan*/  MNT_NOWAIT ; 
 int blocksize ; 
 int count ; 
 int /*<<< orphan*/  dofsizes ; 
 int /*<<< orphan*/  donames ; 
 int /*<<< orphan*/  douser ; 
 int estimate ; 
 int /*<<< orphan*/  func ; 
 int /*<<< orphan*/  getbsize (int /*<<< orphan*/ *,int*) ; 
 struct fstab* getfsfile (char*) ; 
 int getmntinfo (struct statfs**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  header ; 
 int /*<<< orphan*/  headerlen ; 
 int /*<<< orphan*/  quot (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int unused ; 
 int /*<<< orphan*/  usage () ; 

int
main(int argc, char *argv[])
{
	char all = 0;
	struct statfs *mp;
	struct fstab *fs;
	int cnt;

	func = douser;
#ifndef	COMPAT
	header = getbsize(&headerlen,&blocksize);
#endif
	while (--argc > 0 && **++argv == '-') {
		while (*++*argv) {
			switch (**argv) {
			case 'n':
				func = donames;
				break;
			case 'c':
				func = dofsizes;
				break;
			case 'a':
				all = 1;
				break;
			case 'f':
				count = 1;
				break;
			case 'h':
				estimate = 1;
				break;
#ifndef	COMPAT
			case 'k':
				blocksize = 1024;
				break;
#endif	/* COMPAT */
			case 'v':
				unused = 1;
				break;
			default:
				usage();
			}
		}
	}
	if (all) {
		cnt = getmntinfo(&mp,MNT_NOWAIT);
		for (; --cnt >= 0; mp++) {
			if (!strncmp(mp->f_fstypename, "ufs", MFSNAMELEN))
				quot(mp->f_mntfromname, mp->f_mntonname);
		}
	}
	while (--argc >= 0) {
		if ((fs = getfsfile(*argv)) != NULL)
			quot(fs->fs_spec, 0);
		else
			quot(*argv,0);
		argv++;
	}
	return 0;
}