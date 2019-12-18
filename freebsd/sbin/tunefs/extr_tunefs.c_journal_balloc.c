#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ufs2_daddr_t ;
struct TYPE_9__ {int cs_nbfree; } ;
struct cg {TYPE_1__ cg_cs; } ;
struct TYPE_11__ {scalar_t__ d_ccg; struct cg d_cg; } ;
struct TYPE_10__ {int /*<<< orphan*/  fs_bsize; } ;

/* Variables and functions */
 scalar_t__ bwrite (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cgballoc (TYPE_4__*) ; 
 int cgread (TYPE_4__*) ; 
 scalar_t__ cgwrite (TYPE_4__*) ; 
 int /*<<< orphan*/  clrbuf ; 
 TYPE_4__ disk ; 
 int /*<<< orphan*/  fsbtodb (TYPE_2__*,scalar_t__) ; 
 TYPE_2__ sblock ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static ufs2_daddr_t
journal_balloc(void)
{
	ufs2_daddr_t blk;
	struct cg *cgp;
	int valid;
	static int contig = 1;

	cgp = &disk.d_cg;
	for (;;) {
		blk = cgballoc(&disk);
		if (blk > 0)
			break;
		/*
		 * If we failed to allocate a block from this cg, move to
		 * the next.
		 */
		if (cgwrite(&disk) < 0) {
			warn("Failed to write updated cg");
			return (-1);
		}
		while ((valid = cgread(&disk)) == 1) {
			/*
			 * Try to minimize fragmentation by requiring a minimum
			 * number of blocks present.
			 */
			if (cgp->cg_cs.cs_nbfree > 256 * 1024)
				break;
			if (contig == 0 && cgp->cg_cs.cs_nbfree)
				break;
		}
		if (valid)
			continue;
		/*
		 * Try once through looking only for large contiguous regions
		 * and again taking any space we can find.
		 */
		if (contig) {
			contig = 0;
			disk.d_ccg = 0;
			warnx("Journal file fragmented.");
			continue;
		}
		warnx("Failed to find sufficient free blocks for the journal");
		return -1;
	}
	if (bwrite(&disk, fsbtodb(&sblock, blk), clrbuf,
	    sblock.fs_bsize) <= 0) {
		warn("Failed to initialize new block");
		return -1;
	}
	return (blk);
}