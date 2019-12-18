#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fuse_write_out {int dummy; } ;
struct TYPE_2__ {scalar_t__ base; } ;
struct fuse_ticket {int /*<<< orphan*/  tk_data; TYPE_1__ tk_ms_fiov; } ;
struct fuse_statfs_out {int dummy; } ;
struct fuse_read_in {size_t size; } ;
struct fuse_open_out {int dummy; } ;
struct fuse_lk_out {int dummy; } ;
struct fuse_init_out {int dummy; } ;
struct fuse_in_header {int dummy; } ;
struct fuse_entry_out {int dummy; } ;
struct fuse_bmap_out {int dummy; } ;
struct fuse_attr_out {int dummy; } ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;

/* Variables and functions */
 int EINVAL ; 
#define  FUSE_ACCESS 162 
#define  FUSE_BMAP 161 
 size_t FUSE_COMPAT_22_INIT_OUT_SIZE ; 
 size_t FUSE_COMPAT_ATTR_OUT_SIZE ; 
 size_t FUSE_COMPAT_ENTRY_OUT_SIZE ; 
 size_t FUSE_COMPAT_INIT_OUT_SIZE ; 
 size_t FUSE_COMPAT_STATFS_SIZE ; 
#define  FUSE_CREATE 160 
#define  FUSE_DESTROY 159 
#define  FUSE_FLUSH 158 
#define  FUSE_FORGET 157 
#define  FUSE_FSYNC 156 
#define  FUSE_FSYNCDIR 155 
#define  FUSE_GETATTR 154 
#define  FUSE_GETLK 153 
#define  FUSE_GETXATTR 152 
#define  FUSE_INIT 151 
#define  FUSE_LINK 150 
#define  FUSE_LISTXATTR 149 
#define  FUSE_LOOKUP 148 
#define  FUSE_MKDIR 147 
#define  FUSE_MKNOD 146 
#define  FUSE_OPEN 145 
#define  FUSE_OPENDIR 144 
#define  FUSE_READ 143 
#define  FUSE_READDIR 142 
#define  FUSE_READLINK 141 
#define  FUSE_RELEASE 140 
#define  FUSE_RELEASEDIR 139 
#define  FUSE_REMOVEXATTR 138 
#define  FUSE_RENAME 137 
#define  FUSE_RMDIR 136 
#define  FUSE_SETATTR 135 
#define  FUSE_SETLK 134 
#define  FUSE_SETLKW 133 
#define  FUSE_SETXATTR 132 
#define  FUSE_STATFS 131 
#define  FUSE_SYMLINK 130 
#define  FUSE_UNLINK 129 
#define  FUSE_WRITE 128 
 size_t PAGE_SIZE ; 
 int fticket_opcode (struct fuse_ticket*) ; 
 int /*<<< orphan*/  fuse_libabi_geq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  panic (char*,...) ; 

__attribute__((used)) static int
fuse_body_audit(struct fuse_ticket *ftick, size_t blen)
{
	int err = 0;
	enum fuse_opcode opcode;

	opcode = fticket_opcode(ftick);

	switch (opcode) {
	case FUSE_BMAP:
		err = (blen == sizeof(struct fuse_bmap_out)) ? 0 : EINVAL;
		break;

	case FUSE_LINK:
	case FUSE_LOOKUP:
	case FUSE_MKDIR:
	case FUSE_MKNOD:
	case FUSE_SYMLINK:
		if (fuse_libabi_geq(ftick->tk_data, 7, 9)) {
			err = (blen == sizeof(struct fuse_entry_out)) ?
				0 : EINVAL;
		} else {
			err = (blen == FUSE_COMPAT_ENTRY_OUT_SIZE) ? 0 : EINVAL;
		}
		break;

	case FUSE_FORGET:
		panic("FUSE: a handler has been intalled for FUSE_FORGET");
		break;

	case FUSE_GETATTR:
	case FUSE_SETATTR:
		if (fuse_libabi_geq(ftick->tk_data, 7, 9)) {
			err = (blen == sizeof(struct fuse_attr_out)) ? 
			  0 : EINVAL;
		} else {
			err = (blen == FUSE_COMPAT_ATTR_OUT_SIZE) ? 0 : EINVAL;
		}
		break;

	case FUSE_READLINK:
		err = (PAGE_SIZE >= blen) ? 0 : EINVAL;
		break;

	case FUSE_UNLINK:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_RMDIR:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_RENAME:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_OPEN:
		err = (blen == sizeof(struct fuse_open_out)) ? 0 : EINVAL;
		break;

	case FUSE_READ:
		err = (((struct fuse_read_in *)(
		    (char *)ftick->tk_ms_fiov.base +
		    sizeof(struct fuse_in_header)
		    ))->size >= blen) ? 0 : EINVAL;
		break;

	case FUSE_WRITE:
		err = (blen == sizeof(struct fuse_write_out)) ? 0 : EINVAL;
		break;

	case FUSE_STATFS:
		if (fuse_libabi_geq(ftick->tk_data, 7, 4)) {
			err = (blen == sizeof(struct fuse_statfs_out)) ? 
			  0 : EINVAL;
		} else {
			err = (blen == FUSE_COMPAT_STATFS_SIZE) ? 0 : EINVAL;
		}
		break;

	case FUSE_RELEASE:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_FSYNC:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_SETXATTR:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_GETXATTR:
	case FUSE_LISTXATTR:
		/*
		 * These can have varying response lengths, and 0 length
		 * isn't necessarily invalid.
		 */
		err = 0;
		break;

	case FUSE_REMOVEXATTR:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_FLUSH:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_INIT:
		if (blen == sizeof(struct fuse_init_out) ||
		    blen == FUSE_COMPAT_INIT_OUT_SIZE ||
		    blen == FUSE_COMPAT_22_INIT_OUT_SIZE) {
			err = 0;
		} else {
			err = EINVAL;
		}
		break;

	case FUSE_OPENDIR:
		err = (blen == sizeof(struct fuse_open_out)) ? 0 : EINVAL;
		break;

	case FUSE_READDIR:
		err = (((struct fuse_read_in *)(
		    (char *)ftick->tk_ms_fiov.base +
		    sizeof(struct fuse_in_header)
		    ))->size >= blen) ? 0 : EINVAL;
		break;

	case FUSE_RELEASEDIR:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_FSYNCDIR:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_GETLK:
		err = (blen == sizeof(struct fuse_lk_out)) ? 0 : EINVAL;
		break;

	case FUSE_SETLK:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_SETLKW:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_ACCESS:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	case FUSE_CREATE:
		if (fuse_libabi_geq(ftick->tk_data, 7, 9)) {
			err = (blen == sizeof(struct fuse_entry_out) +
			    sizeof(struct fuse_open_out)) ? 0 : EINVAL;
		} else {
			err = (blen == FUSE_COMPAT_ENTRY_OUT_SIZE +
			    sizeof(struct fuse_open_out)) ? 0 : EINVAL;
		}
		break;

	case FUSE_DESTROY:
		err = (blen == 0) ? 0 : EINVAL;
		break;

	default:
		panic("FUSE: opcodes out of sync (%d)\n", opcode);
	}

	return err;
}