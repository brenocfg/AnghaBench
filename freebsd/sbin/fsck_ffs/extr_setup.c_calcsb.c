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
typedef  int u_int ;
struct fsrecovery {scalar_t__ fsr_magic; int /*<<< orphan*/  fsr_ncg; int /*<<< orphan*/  fsr_sblkno; int /*<<< orphan*/  fsr_fsbtodb; int /*<<< orphan*/  fsr_fpg; } ;
struct fs {scalar_t__ fs_magic; int /*<<< orphan*/  fs_ncg; int /*<<< orphan*/  fs_sblkno; int /*<<< orphan*/  fs_fsbtodb; int /*<<< orphan*/  fs_fpg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 int /*<<< orphan*/  EEXIT ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 char* Malloc (int) ; 
 int SBLOCK_UFS2 ; 
 scalar_t__ blread (int,char*,int,int) ; 
 int dev_bsize ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (struct fs*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
calcsb(char *dev, int devfd, struct fs *fs)
{
	struct fsrecovery *fsr;
	char *fsrbuf;
	u_int secsize;

	/*
	 * We need fragments-per-group and the partition-size.
	 *
	 * Newfs stores these details at the end of the boot block area
	 * at the start of the filesystem partition. If they have been
	 * overwritten by a boot block, we fail. But usually they are
	 * there and we can use them.
	 */
	if (ioctl(devfd, DIOCGSECTORSIZE, &secsize) == -1)
		return (0);
	fsrbuf = Malloc(secsize);
	if (fsrbuf == NULL)
		errx(EEXIT, "calcsb: cannot allocate recovery buffer");
	if (blread(devfd, fsrbuf,
	    (SBLOCK_UFS2 - secsize) / dev_bsize, secsize) != 0)
		return (0);
	fsr = (struct fsrecovery *)&fsrbuf[secsize - sizeof *fsr];
	if (fsr->fsr_magic != FS_UFS2_MAGIC)
		return (0);
	memset(fs, 0, sizeof(struct fs));
	fs->fs_fpg = fsr->fsr_fpg;
	fs->fs_fsbtodb = fsr->fsr_fsbtodb;
	fs->fs_sblkno = fsr->fsr_sblkno;
	fs->fs_magic = fsr->fsr_magic;
	fs->fs_ncg = fsr->fsr_ncg;
	free(fsrbuf);
	return (1);
}