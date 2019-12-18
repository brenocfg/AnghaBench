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
typedef  int /*<<< orphan*/  ufs2_daddr_t ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ visitlbn ; 

__attribute__((used)) static void
null_visit(ino_t ino, ufs_lbn_t lbn, ufs2_daddr_t blk, int frags)
{
	if (lbn > 0)
		visitlbn = lbn;
}