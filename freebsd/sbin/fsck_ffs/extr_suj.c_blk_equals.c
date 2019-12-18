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
typedef  scalar_t__ ufs_lbn_t ;
typedef  scalar_t__ ufs2_daddr_t ;
struct jblkrec {scalar_t__ jb_ino; scalar_t__ jb_lbn; scalar_t__ jb_blkno; scalar_t__ jb_oldfrags; int jb_frags; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */

__attribute__((used)) static int
blk_equals(struct jblkrec *brec, ino_t ino, ufs_lbn_t lbn, ufs2_daddr_t start,
    int frags)
{

	if (brec->jb_ino != ino || brec->jb_lbn != lbn)
		return (0);
	if (brec->jb_blkno + brec->jb_oldfrags != start)
		return (0);
	if (brec->jb_frags < frags)
		return (0);
	return (1);
}