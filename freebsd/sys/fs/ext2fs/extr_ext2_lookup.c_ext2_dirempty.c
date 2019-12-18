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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct inode {scalar_t__ i_size; } ;
struct ext2fs_direct_2 {scalar_t__ e2d_reclen; scalar_t__ e2d_ino; int e2d_namlen; char* e2d_name; } ;
struct dirtemplate {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ ino_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int IO_NODELOCKED ; 
 int IO_NOMACCHECK ; 
 int /*<<< orphan*/  ITOV (struct inode*) ; 
 int /*<<< orphan*/  MINDIRSIZ ; 
 int /*<<< orphan*/  NOCRED ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int,struct ucred*,int /*<<< orphan*/ ,scalar_t__*,struct thread*) ; 

int
ext2_dirempty(struct inode *ip, ino_t parentino, struct ucred *cred)
{
	off_t off;
	struct dirtemplate dbuf;
	struct ext2fs_direct_2 *dp = (struct ext2fs_direct_2 *)&dbuf;
	int error, namlen;
	ssize_t count;
#define	MINDIRSIZ (sizeof(struct dirtemplate) / 2)

	for (off = 0; off < ip->i_size; off += dp->e2d_reclen) {
		error = vn_rdwr(UIO_READ, ITOV(ip), (caddr_t)dp, MINDIRSIZ,
		    off, UIO_SYSSPACE, IO_NODELOCKED | IO_NOMACCHECK, cred,
		    NOCRED, &count, (struct thread *)0);
		/*
		 * Since we read MINDIRSIZ, residual must
		 * be 0 unless we're at end of file.
		 */
		if (error || count != 0)
			return (0);
		/* avoid infinite loops */
		if (dp->e2d_reclen == 0)
			return (0);
		/* skip empty entries */
		if (dp->e2d_ino == 0)
			continue;
		/* accept only "." and ".." */
		namlen = dp->e2d_namlen;
		if (namlen > 2)
			return (0);
		if (dp->e2d_name[0] != '.')
			return (0);
		/*
		 * At this point namlen must be 1 or 2.
		 * 1 implies ".", 2 implies ".." if second
		 * char is also "."
		 */
		if (namlen == 1)
			continue;
		if (dp->e2d_name[1] == '.' && dp->e2d_ino == parentino)
			continue;
		return (0);
	}
	return (1);
}