#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
typedef  scalar_t__ ufs1_daddr_t ;
struct suj_cg {int sc_dirty; struct cg* sc_cgp; } ;
struct cg {int dummy; } ;
struct TYPE_6__ {int fs_frag; } ;

/* Variables and functions */
 int /*<<< orphan*/ * cg_blksfree (struct cg*) ; 
 struct suj_cg* cg_lookup (int) ; 
 scalar_t__ debug ; 
 int dtog (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dtogd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffs_setblock (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ fragstoblks (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  freeblocks ; 
 int /*<<< orphan*/  freefrags ; 
 TYPE_1__* fs ; 
 scalar_t__ isclr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  printf (char*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  setbit (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
blk_free(ufs2_daddr_t bno, int mask, int frags)
{
	ufs1_daddr_t fragno, cgbno;
	struct suj_cg *sc;
	struct cg *cgp;
	int i, cg;
	uint8_t *blksfree;

	if (debug)
		printf("Freeing %d frags at blk %jd mask 0x%x\n",
		    frags, bno, mask);
	cg = dtog(fs, bno);
	sc = cg_lookup(cg);
	cgp = sc->sc_cgp;
	cgbno = dtogd(fs, bno);
	blksfree = cg_blksfree(cgp);

	/*
	 * If it's not allocated we only wrote the journal entry
	 * and never the bitmaps.  Here we unconditionally clear and
	 * resolve the cg summary later.
	 */
	if (frags == fs->fs_frag && mask == 0) {
		fragno = fragstoblks(fs, cgbno);
		ffs_setblock(fs, blksfree, fragno);
		freeblocks++;
	} else {
		/*
		 * deallocate the fragment
		 */
		for (i = 0; i < frags; i++)
			if ((mask & (1 << i)) == 0 && isclr(blksfree, cgbno +i)) {
				freefrags++;
				setbit(blksfree, cgbno + i);
			}
	}
	sc->sc_dirty = 1;
}