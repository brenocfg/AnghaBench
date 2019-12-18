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
struct vnode {int /*<<< orphan*/  v_type; } ;
struct socket {int /*<<< orphan*/  so_type; } ;
struct file {int f_type; struct vnode* f_vnode; struct socket* f_data; } ;
typedef  int /*<<< orphan*/  cloudabi_filetype_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOUDABI_FILETYPE_BLOCK_DEVICE ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_CHARACTER_DEVICE ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_DIRECTORY ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_PROCESS ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_REGULAR_FILE ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_SHARED_MEMORY ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_SOCKET_DGRAM ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_SOCKET_STREAM ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_SYMBOLIC_LINK ; 
 int /*<<< orphan*/  CLOUDABI_FILETYPE_UNKNOWN ; 
#define  DTYPE_FIFO 142 
#define  DTYPE_PIPE 141 
#define  DTYPE_PROCDESC 140 
#define  DTYPE_SHM 139 
#define  DTYPE_SOCKET 138 
#define  DTYPE_VNODE 137 
#define  SOCK_DGRAM 136 
#define  SOCK_STREAM 135 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
#define  VREG 129 
#define  VSOCK 128 

cloudabi_filetype_t
cloudabi_convert_filetype(const struct file *fp)
{
	struct socket *so;
	struct vnode *vp;

	switch (fp->f_type) {
	case DTYPE_FIFO:
		return (CLOUDABI_FILETYPE_SOCKET_STREAM);
	case DTYPE_PIPE:
		return (CLOUDABI_FILETYPE_SOCKET_STREAM);
	case DTYPE_PROCDESC:
		return (CLOUDABI_FILETYPE_PROCESS);
	case DTYPE_SHM:
		return (CLOUDABI_FILETYPE_SHARED_MEMORY);
	case DTYPE_SOCKET:
		so = fp->f_data;
		switch (so->so_type) {
		case SOCK_DGRAM:
			return (CLOUDABI_FILETYPE_SOCKET_DGRAM);
		case SOCK_STREAM:
			return (CLOUDABI_FILETYPE_SOCKET_STREAM);
		default:
			return (CLOUDABI_FILETYPE_UNKNOWN);
		}
	case DTYPE_VNODE:
		vp = fp->f_vnode;
		switch (vp->v_type) {
		case VBLK:
			return (CLOUDABI_FILETYPE_BLOCK_DEVICE);
		case VCHR:
			return (CLOUDABI_FILETYPE_CHARACTER_DEVICE);
		case VDIR:
			return (CLOUDABI_FILETYPE_DIRECTORY);
		case VFIFO:
			return (CLOUDABI_FILETYPE_SOCKET_STREAM);
		case VLNK:
			return (CLOUDABI_FILETYPE_SYMBOLIC_LINK);
		case VREG:
			return (CLOUDABI_FILETYPE_REGULAR_FILE);
		case VSOCK:
			return (CLOUDABI_FILETYPE_SOCKET_STREAM);
		default:
			return (CLOUDABI_FILETYPE_UNKNOWN);
		}
	default:
		return (CLOUDABI_FILETYPE_UNKNOWN);
	}
}