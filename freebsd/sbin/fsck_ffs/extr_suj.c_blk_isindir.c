#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ufs_lbn_t ;
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
struct suj_blk {int /*<<< orphan*/  sb_recs; } ;
struct jblkrec {scalar_t__ jb_op; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {scalar_t__ sr_rec; } ;
struct TYPE_3__ {int /*<<< orphan*/  fs_frag; } ;

/* Variables and functions */
 scalar_t__ JOP_FREEBLK ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ blk_equals (struct jblkrec*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_isfree (int /*<<< orphan*/ ) ; 
 struct suj_blk* blk_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* fs ; 
 int /*<<< orphan*/  srechd ; 

__attribute__((used)) static int
blk_isindir(ufs2_daddr_t blk, ino_t ino, ufs_lbn_t lbn)
{
	struct suj_blk *sblk;
	struct jblkrec *brec;

	sblk = blk_lookup(blk, 0);
	if (sblk == NULL)
		return (1);
	if (TAILQ_EMPTY(&sblk->sb_recs))
		return (1);
	brec = (struct jblkrec *)TAILQ_LAST(&sblk->sb_recs, srechd)->sr_rec;
	if (blk_equals(brec, ino, lbn, blk, fs->fs_frag))
		if (brec->jb_op == JOP_FREEBLK)
			return (!blk_isfree(blk));
	return (0);
}