#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int ufs2_daddr_t ;
struct fs {int fs_ipg; int fs_fpg; } ;
struct TYPE_2__ {int cs_ndir; } ;
struct cg {int cg_cgx; TYPE_1__ cg_cs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHAR_BIT ; 
 int /*<<< orphan*/  cg_blksfree (struct cg*) ; 
 int /*<<< orphan*/  cg_inosused (struct cg*) ; 
 int /*<<< orphan*/  check_maps (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  freeblks ; 
 int /*<<< orphan*/  freedirs ; 
 int /*<<< orphan*/  freefiles ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfatal (char*,int) ; 
 struct fs sblock ; 

void
update_maps(
	struct cg *oldcg,	/* cylinder group of claimed allocations */
	struct cg *newcg,	/* cylinder group of determined allocations */
	int usesysctl)		/* 1 => use sysctl interface to update maps */
{
	int inomapsize, excessdirs;
	struct fs *fs = &sblock;

	inomapsize = howmany(fs->fs_ipg, CHAR_BIT);
	excessdirs = oldcg->cg_cs.cs_ndir - newcg->cg_cs.cs_ndir;
	if (excessdirs < 0) {
		pfatal("LOST %d DIRECTORIES\n", -excessdirs);
		excessdirs = 0;
	}
	if (excessdirs > 0)
		check_maps(cg_inosused(newcg), cg_inosused(oldcg), inomapsize,
		    oldcg->cg_cgx * (ufs2_daddr_t)fs->fs_ipg, "DIR", freedirs,
		    0, excessdirs, usesysctl);
	check_maps(cg_inosused(newcg), cg_inosused(oldcg), inomapsize,
	    oldcg->cg_cgx * (ufs2_daddr_t)fs->fs_ipg, "FILE", freefiles,
	    excessdirs, fs->fs_ipg, usesysctl);
	check_maps(cg_blksfree(oldcg), cg_blksfree(newcg),
	    howmany(fs->fs_fpg, CHAR_BIT),
	    oldcg->cg_cgx * (ufs2_daddr_t)fs->fs_fpg, "FRAG",
	    freeblks, 0, fs->fs_fpg, usesysctl);
}