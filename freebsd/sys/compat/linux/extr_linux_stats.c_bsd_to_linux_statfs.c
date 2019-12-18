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
typedef  int uint64_t ;
struct TYPE_4__ {int /*<<< orphan*/ * val; } ;
struct statfs {int f_blocks; int f_bfree; int f_files; int f_bsize; int f_bavail; int f_ffree; TYPE_2__ f_fsid; int /*<<< orphan*/  f_fstypename; } ;
struct TYPE_3__ {int /*<<< orphan*/ * val; } ;
struct l_statfs {int f_bsize; int f_blocks; int f_bfree; int f_bavail; int f_ffree; int f_files; int f_frsize; int /*<<< orphan*/  f_spare; scalar_t__ f_flags; int /*<<< orphan*/  f_namelen; TYPE_1__ f_fsid; int /*<<< orphan*/  f_type; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int LINUX_HIBITS ; 
 int /*<<< orphan*/  MAXNAMLEN ; 
 int /*<<< orphan*/  bsd_to_linux_ftype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
bsd_to_linux_statfs(struct statfs *bsd_statfs, struct l_statfs *linux_statfs)
{
#if defined(__i386__) || (defined(__amd64__) && defined(COMPAT_LINUX32))
	uint64_t tmp;

#define	LINUX_HIBITS	0xffffffff00000000ULL

	tmp = bsd_statfs->f_blocks | bsd_statfs->f_bfree | bsd_statfs->f_files |
	    bsd_statfs->f_bsize;
	if ((bsd_statfs->f_bavail != -1 && (bsd_statfs->f_bavail & LINUX_HIBITS)) ||
	    (bsd_statfs->f_ffree != -1 && (bsd_statfs->f_ffree & LINUX_HIBITS)) ||
	    (tmp & LINUX_HIBITS))
		return (EOVERFLOW);
#undef	LINUX_HIBITS
#endif
	linux_statfs->f_type = bsd_to_linux_ftype(bsd_statfs->f_fstypename);
	linux_statfs->f_bsize = bsd_statfs->f_bsize;
	linux_statfs->f_blocks = bsd_statfs->f_blocks;
	linux_statfs->f_bfree = bsd_statfs->f_bfree;
	linux_statfs->f_bavail = bsd_statfs->f_bavail;
	linux_statfs->f_ffree = bsd_statfs->f_ffree;
	linux_statfs->f_files = bsd_statfs->f_files;
	linux_statfs->f_fsid.val[0] = bsd_statfs->f_fsid.val[0];
	linux_statfs->f_fsid.val[1] = bsd_statfs->f_fsid.val[1];
	linux_statfs->f_namelen = MAXNAMLEN;
	linux_statfs->f_frsize = bsd_statfs->f_bsize;
	linux_statfs->f_flags = 0;
	memset(linux_statfs->f_spare, 0, sizeof(linux_statfs->f_spare));

	return (0);
}