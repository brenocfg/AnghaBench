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
struct ufs2_dinode {int /*<<< orphan*/  di_ib; int /*<<< orphan*/  di_db; int /*<<< orphan*/  di_extb; void* di_extsize; void* di_flags; void* di_kernflags; void* di_gen; void* di_ctimensec; void* di_birthnsec; void* di_ctime; void* di_birthtime; void* di_mtimensec; void* di_mtime; void* di_atimensec; void* di_atime; void* di_blocks; void* di_size; void* di_blksize; void* di_gid; void* di_uid; void* di_nlink; void* di_mode; } ;

/* Variables and functions */
 void* bswap16 (void*) ; 
 void* bswap32 (void*) ; 
 void* bswap64 (void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
ffs_dinode2_swap(struct ufs2_dinode *o, struct ufs2_dinode *n)
{
	n->di_mode = bswap16(o->di_mode);
	n->di_nlink = bswap16(o->di_nlink);
	n->di_uid = bswap32(o->di_uid);
	n->di_gid = bswap32(o->di_gid);
	n->di_blksize = bswap32(o->di_blksize);
	n->di_size = bswap64(o->di_size);
	n->di_blocks = bswap64(o->di_blocks);
	n->di_atime = bswap64(o->di_atime);
	n->di_atimensec = bswap32(o->di_atimensec);
	n->di_mtime = bswap64(o->di_mtime);
	n->di_mtimensec = bswap32(o->di_mtimensec);
	n->di_ctime = bswap64(o->di_ctime);
	n->di_ctimensec = bswap32(o->di_ctimensec);
	n->di_birthtime = bswap64(o->di_ctime);
	n->di_birthnsec = bswap32(o->di_ctimensec);
	n->di_gen = bswap32(o->di_gen);
	n->di_kernflags = bswap32(o->di_kernflags);
	n->di_flags = bswap32(o->di_flags);
	n->di_extsize = bswap32(o->di_extsize);
	memcpy(n->di_extb, o->di_extb, sizeof(n->di_extb));
	memcpy(n->di_db, o->di_db, sizeof(n->di_db));
	memcpy(n->di_ib, o->di_ib, sizeof(n->di_ib));
}