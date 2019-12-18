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
typedef  int /*<<< orphan*/  uint64_t ;
struct vnode {int dummy; } ;
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct fuse_mknod_in {scalar_t__ rdev; int /*<<< orphan*/  mode; } ;
struct fuse_dispatcher {struct fuse_mknod_in* indata; } ;
struct componentname {int cn_namelen; int /*<<< orphan*/  cn_nameptr; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;

/* Variables and functions */
 int FUSE_MKNOD ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct thread*,struct ucred*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vnode_mount (struct vnode*) ; 

__attribute__((used)) static void
fdisp_make_mknod_for_fallback(
	struct fuse_dispatcher *fdip,
	struct componentname *cnp,
	struct vnode *dvp,
	uint64_t parentnid,
	struct thread *td,
	struct ucred *cred,
	mode_t mode,
	enum fuse_opcode *op)
{
	struct fuse_mknod_in *fmni;

	fdisp_init(fdip, sizeof(*fmni) + cnp->cn_namelen + 1);
	*op = FUSE_MKNOD;
	fdisp_make(fdip, *op, vnode_mount(dvp), parentnid, td, cred);
	fmni = fdip->indata;
	fmni->mode = mode;
	fmni->rdev = 0;
	memcpy((char *)fdip->indata + sizeof(*fmni), cnp->cn_nameptr,
	    cnp->cn_namelen);
	((char *)fdip->indata)[sizeof(*fmni) + cnp->cn_namelen] = '\0';
}