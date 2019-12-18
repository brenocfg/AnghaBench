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
struct jblkrec {int jb_oldfrags; int jb_frags; } ;

/* Variables and functions */

__attribute__((used)) static void
blk_setmask(struct jblkrec *brec, int *mask)
{
	int i;

	for (i = brec->jb_oldfrags; i < brec->jb_oldfrags + brec->jb_frags; i++)
		*mask |= 1 << i;
}