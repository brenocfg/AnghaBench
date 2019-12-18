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
struct fha_info {int /*<<< orphan*/  locktype; } ;
typedef  int rpcproc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LK_EXCLUSIVE ; 
 int /*<<< orphan*/  LK_SHARED ; 
#define  NFSPROC_ACCESS 150 
#define  NFSPROC_COMMIT 149 
#define  NFSPROC_CREATE 148 
#define  NFSPROC_FSINFO 147 
#define  NFSPROC_FSSTAT 146 
#define  NFSPROC_GETATTR 145 
#define  NFSPROC_LINK 144 
#define  NFSPROC_LOOKUP 143 
#define  NFSPROC_MKDIR 142 
#define  NFSPROC_MKNOD 141 
#define  NFSPROC_NOOP 140 
#define  NFSPROC_NULL 139 
#define  NFSPROC_PATHCONF 138 
#define  NFSPROC_READ 137 
#define  NFSPROC_READDIR 136 
#define  NFSPROC_READDIRPLUS 135 
#define  NFSPROC_READLINK 134 
#define  NFSPROC_REMOVE 133 
#define  NFSPROC_RENAME 132 
#define  NFSPROC_RMDIR 131 
#define  NFSPROC_SETATTR 130 
#define  NFSPROC_SYMLINK 129 
#define  NFSPROC_WRITE 128 

void
fhanew_set_locktype(rpcproc_t procnum, struct fha_info *info)
{
	switch (procnum) {
	case NFSPROC_NULL:
	case NFSPROC_GETATTR:
	case NFSPROC_LOOKUP:
	case NFSPROC_ACCESS:
	case NFSPROC_READLINK:
	case NFSPROC_READ:
	case NFSPROC_READDIR:
	case NFSPROC_READDIRPLUS:
	case NFSPROC_WRITE:
		info->locktype = LK_SHARED;
		break;
	case NFSPROC_SETATTR:
	case NFSPROC_CREATE:
	case NFSPROC_MKDIR:
	case NFSPROC_SYMLINK:
	case NFSPROC_MKNOD:
	case NFSPROC_REMOVE:
	case NFSPROC_RMDIR:
	case NFSPROC_RENAME:
	case NFSPROC_LINK:
	case NFSPROC_FSSTAT:
	case NFSPROC_FSINFO:
	case NFSPROC_PATHCONF:
	case NFSPROC_COMMIT:
	case NFSPROC_NOOP:
		info->locktype = LK_EXCLUSIVE;
		break;
	}
}