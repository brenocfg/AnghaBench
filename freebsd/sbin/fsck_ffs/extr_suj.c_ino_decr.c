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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int DIP (union dinode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIP_SET (union dinode*,int /*<<< orphan*/ ,int) ; 
 int IFDIR ; 
 int IFMT ; 
 scalar_t__ debug ; 
 int /*<<< orphan*/  di_mode ; 
 int /*<<< orphan*/  di_nlink ; 
 int /*<<< orphan*/  err_suj (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  ino_dirty (scalar_t__) ; 
 union dinode* ino_read (scalar_t__) ; 
 int /*<<< orphan*/  ino_reclaim (union dinode*,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
ino_decr(ino_t ino)
{
	union dinode *ip;
	int reqlink;
	int nlink;
	int mode;

	ip = ino_read(ino);
	nlink = DIP(ip, di_nlink);
	mode = DIP(ip, di_mode);
	if (nlink < 1)
		err_suj("Inode %d link count %d invalid\n", ino, nlink);
	if (mode == 0)
		err_suj("Inode %d has a link of %d with 0 mode\n", ino, nlink);
	nlink--;
	if ((mode & IFMT) == IFDIR)
		reqlink = 2;
	else
		reqlink = 1;
	if (nlink < reqlink) {
		if (debug)
			printf("ino %ju not enough links to live %d < %d\n",
			    (uintmax_t)ino, nlink, reqlink);
		ino_reclaim(ip, ino, mode);
		return;
	}
	DIP_SET(ip, di_nlink, nlink);
	ino_dirty(ino);
}