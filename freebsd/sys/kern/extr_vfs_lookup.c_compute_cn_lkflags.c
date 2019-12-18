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
struct mount {int mnt_kern_flag; } ;

/* Variables and functions */
 int ISDOTDOT ; 
 int LK_EXCLUSIVE ; 
 int LK_NODDLKTREAT ; 
 int LK_SHARED ; 
 int MNTK_LOOKUP_EXCL_DOTDOT ; 
 int MNTK_LOOKUP_SHARED ; 

__attribute__((used)) static int
compute_cn_lkflags(struct mount *mp, int lkflags, int cnflags)
{

	if (mp == NULL || ((lkflags & LK_SHARED) &&
	    (!(mp->mnt_kern_flag & MNTK_LOOKUP_SHARED) ||
	    ((cnflags & ISDOTDOT) &&
	    (mp->mnt_kern_flag & MNTK_LOOKUP_EXCL_DOTDOT))))) {
		lkflags &= ~LK_SHARED;
		lkflags |= LK_EXCLUSIVE;
	}
	lkflags |= LK_NODDLKTREAT;
	return (lkflags);
}