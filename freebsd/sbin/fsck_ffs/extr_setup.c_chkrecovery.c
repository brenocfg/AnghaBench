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
struct fsrecovery {scalar_t__ fsr_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCGSECTORSIZE ; 
 scalar_t__ FS_UFS2_MAGIC ; 
 char* Malloc (int) ; 
 int SBLOCK_UFS2 ; 
 scalar_t__ blread (int,char*,int,int) ; 
 int dev_bsize ; 
 int /*<<< orphan*/  free (char*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
chkrecovery(int devfd)
{
	struct fsrecovery *fsr;
	char *fsrbuf;
	u_int secsize;

	/*
	 * Could not determine if backup material exists, so do not
	 * offer to create it.
	 */
	if (ioctl(devfd, DIOCGSECTORSIZE, &secsize) == -1 ||
	    (fsrbuf = Malloc(secsize)) == NULL ||
	    blread(devfd, fsrbuf, (SBLOCK_UFS2 - secsize) / dev_bsize,
	      secsize) != 0)
		return (1);
	/*
	 * Recovery material has already been created, so do not
	 * need to create it again.
	 */
	fsr = (struct fsrecovery *)&fsrbuf[secsize - sizeof *fsr];
	if (fsr->fsr_magic == FS_UFS2_MAGIC) {
		free(fsrbuf);
		return (1);
	}
	/*
	 * Recovery material has not been created and can be if desired.
	 */
	free(fsrbuf);
	return (0);
}