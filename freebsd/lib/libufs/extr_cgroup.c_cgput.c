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
struct fs {int fs_metackhash; int /*<<< orphan*/  fs_cgsize; } ;
struct uufsd {struct fs d_fs; } ;
struct cg {int /*<<< orphan*/  cg_cgx; int /*<<< orphan*/  cg_ckhash; } ;

/* Variables and functions */
 int CK_CYLGRP ; 
 int /*<<< orphan*/  ERROR (struct uufsd*,char*) ; 
 int bwrite (struct uufsd*,int /*<<< orphan*/ ,struct cg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calculate_crc32c (long,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgtod (struct fs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsbtodb (struct fs*,int /*<<< orphan*/ ) ; 

int
cgput(struct uufsd *disk, struct cg *cgp)
{
	struct fs *fs;

	fs = &disk->d_fs;
	if ((fs->fs_metackhash & CK_CYLGRP) != 0) {
		cgp->cg_ckhash = 0;
		cgp->cg_ckhash =
		    calculate_crc32c(~0L, (void *)cgp, fs->fs_cgsize);
	}
	if (bwrite(disk, fsbtodb(fs, cgtod(fs, cgp->cg_cgx)), cgp,
	    fs->fs_cgsize) == -1) {
		ERROR(disk, "unable to write cylinder group");
		return (-1);
	}
	return (0);
}