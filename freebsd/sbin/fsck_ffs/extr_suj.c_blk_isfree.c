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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct suj_cg {int /*<<< orphan*/  sc_cgp; } ;

/* Variables and functions */
 int /*<<< orphan*/  cg_blksfree (int /*<<< orphan*/ ) ; 
 struct suj_cg* cg_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtog (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtogd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ffs_isblock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs ; 

__attribute__((used)) static int
blk_isfree(ufs2_daddr_t bno)
{
	struct suj_cg *sc;

	sc = cg_lookup(dtog(fs, bno));
	return ffs_isblock(fs, cg_blksfree(sc->sc_cgp), dtogd(fs, bno));
}