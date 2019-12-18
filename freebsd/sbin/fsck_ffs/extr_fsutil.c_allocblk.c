#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ufs2_daddr_t ;
struct TYPE_7__ {long cs_nffree; int /*<<< orphan*/  cs_nbfree; } ;
struct cg {TYPE_2__ cg_cs; } ;
struct TYPE_6__ {struct cg* b_cg; } ;
struct bufarea {TYPE_1__ b_un; } ;
struct TYPE_8__ {long fs_frag; } ;

/* Variables and functions */
 int /*<<< orphan*/  cg_blksfree (struct cg*) ; 
 int /*<<< orphan*/  cgdirty (struct bufarea*) ; 
 struct bufarea* cglookup (int) ; 
 int /*<<< orphan*/  check_cgmagic (int,struct bufarea*) ; 
 int /*<<< orphan*/  clrbit (int /*<<< orphan*/ ,int) ; 
 int dtog (TYPE_3__*,int) ; 
 int dtogd (TYPE_3__*,int) ; 
 int maxfsblock ; 
 long n_blks ; 
 TYPE_3__ sblock ; 
 int /*<<< orphan*/  setbmap (int) ; 
 scalar_t__ testbmap (int) ; 

ufs2_daddr_t
allocblk(long frags)
{
	int i, j, k, cg, baseblk;
	struct bufarea *cgbp;
	struct cg *cgp;

	if (frags <= 0 || frags > sblock.fs_frag)
		return (0);
	for (i = 0; i < maxfsblock - sblock.fs_frag; i += sblock.fs_frag) {
		for (j = 0; j <= sblock.fs_frag - frags; j++) {
			if (testbmap(i + j))
				continue;
			for (k = 1; k < frags; k++)
				if (testbmap(i + j + k))
					break;
			if (k < frags) {
				j += k;
				continue;
			}
			cg = dtog(&sblock, i + j);
			cgbp = cglookup(cg);
			cgp = cgbp->b_un.b_cg;
			if (!check_cgmagic(cg, cgbp))
				return (0);
			baseblk = dtogd(&sblock, i + j);
			for (k = 0; k < frags; k++) {
				setbmap(i + j + k);
				clrbit(cg_blksfree(cgp), baseblk + k);
			}
			n_blks += frags;
			if (frags == sblock.fs_frag)
				cgp->cg_cs.cs_nbfree--;
			else
				cgp->cg_cs.cs_nffree -= frags;
			cgdirty(cgbp);
			return (i + j);
		}
	}
	return (0);
}