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
typedef  union dinode {int dummy; } dinode ;
typedef  int /*<<< orphan*/  ufs_lbn_t ;
typedef  scalar_t__ ufs2_daddr_t ;
typedef  int /*<<< orphan*/  ino_t ;

/* Variables and functions */
 scalar_t__ DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 scalar_t__ ino_blkatoff (union dinode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 union dinode* ino_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
blk_isat(ino_t ino, ufs_lbn_t lbn, ufs2_daddr_t blk, int *frags)
{
	union dinode *ip;
	ufs2_daddr_t nblk;

	ip = ino_read(ino);

	if (DIP(ip, di_nlink) == 0 || DIP(ip, di_mode) == 0)
		return (0);
	nblk = ino_blkatoff(ip, ino, lbn, frags);

	return (nblk == blk);
}