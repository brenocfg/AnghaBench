#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct vop_create_args {struct vattr* a_vap; struct componentname* a_cnp; struct vnode** a_vpp; struct vnode* a_dvp; } ;
struct vnode {int dummy; } ;
struct vattr {scalar_t__ va_type; int /*<<< orphan*/  va_mode; } ;
struct ucred {int dummy; } ;
struct thread {TYPE_2__* td_proc; } ;
struct mount {int dummy; } ;
struct fuse_release_in {int flags; int /*<<< orphan*/  fh; int /*<<< orphan*/  umask; int /*<<< orphan*/  mode; } ;
struct fuse_open_out {int /*<<< orphan*/  open_flags; int /*<<< orphan*/  attr_valid_nsec; int /*<<< orphan*/  attr_valid; int /*<<< orphan*/  attr; int /*<<< orphan*/  fh; int /*<<< orphan*/  nodeid; } ;
struct fuse_open_in {int flags; int /*<<< orphan*/  fh; int /*<<< orphan*/  umask; int /*<<< orphan*/  mode; } ;
struct fuse_entry_out {int /*<<< orphan*/  open_flags; int /*<<< orphan*/  attr_valid_nsec; int /*<<< orphan*/  attr_valid; int /*<<< orphan*/  attr; int /*<<< orphan*/  fh; int /*<<< orphan*/  nodeid; } ;
struct fuse_dispatcher {int /*<<< orphan*/  tick; struct fuse_release_in* indata; struct fuse_open_out* answ; } ;
struct fuse_data {int dummy; } ;
struct fuse_create_in {int flags; int /*<<< orphan*/  fh; int /*<<< orphan*/  umask; int /*<<< orphan*/  mode; } ;
struct componentname {int cn_namelen; int /*<<< orphan*/  cn_nameptr; struct ucred* cn_cred; struct thread* cn_thread; } ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  fdi ;
typedef  enum fuse_opcode { ____Placeholder_fuse_opcode } fuse_opcode ;
struct TYPE_6__ {int /*<<< orphan*/  nid; } ;
struct TYPE_5__ {TYPE_1__* p_fd; } ;
struct TYPE_4__ {int /*<<< orphan*/  fd_cmask; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_VOP_ELOCKED (struct vnode*,char*) ; 
 int EINVAL ; 
 int ENOSYS ; 
 int ENXIO ; 
 int /*<<< orphan*/  FUFH_RDWR ; 
 int FUSE_CREATE ; 
 int FUSE_OPEN ; 
 int FUSE_RELEASE ; 
 int /*<<< orphan*/  MAKEIMODE (scalar_t__,int /*<<< orphan*/ ) ; 
 int O_CREAT ; 
 int O_RDWR ; 
 scalar_t__ VREG ; 
 scalar_t__ VSOCK ; 
 TYPE_3__* VTOFUD (struct vnode*) ; 
 int /*<<< orphan*/  bzero (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  cache_purge_negative (struct vnode*) ; 
 int /*<<< orphan*/  fdisp_destroy (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fdisp_init (struct fuse_dispatcher*,int) ; 
 int /*<<< orphan*/  fdisp_make (struct fuse_dispatcher*,int,struct mount*,int /*<<< orphan*/ ,struct thread*,struct ucred*) ; 
 int /*<<< orphan*/  fdisp_make_mknod_for_fallback (struct fuse_dispatcher*,struct componentname*,struct vnode*,int /*<<< orphan*/ ,struct thread*,struct ucred*,int /*<<< orphan*/ ,int*) ; 
 int fdisp_wait_answ (struct fuse_dispatcher*) ; 
 int /*<<< orphan*/  fsess_isimpl (struct mount*,int) ; 
 int /*<<< orphan*/  fsess_set_notimpl (struct mount*,int) ; 
 int /*<<< orphan*/  fuse_filehandle_init (struct vnode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct thread*,struct ucred*,struct fuse_open_out*) ; 
 struct fuse_data* fuse_get_mpdata (struct mount*) ; 
 int /*<<< orphan*/  fuse_insert_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_insert_message (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fuse_internal_cache_attrs (struct vnode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int fuse_internal_checkentry (struct fuse_open_out*,scalar_t__) ; 
 int /*<<< orphan*/  fuse_internal_forget_callback ; 
 int fuse_internal_mknod (struct vnode*,struct vnode**,struct componentname*,struct vattr*) ; 
 scalar_t__ fuse_isdeadfs (struct vnode*) ; 
 scalar_t__ fuse_libabi_geq (struct fuse_data*,int,int) ; 
 int /*<<< orphan*/  fuse_vnode_clear_attr_cache (struct vnode*) ; 
 int fuse_vnode_get (struct mount*,struct fuse_open_out*,int /*<<< orphan*/ ,struct vnode*,struct vnode**,struct componentname*,scalar_t__) ; 
 int /*<<< orphan*/  fuse_vnode_open (struct vnode*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 struct mount* vnode_mount (struct vnode*) ; 

__attribute__((used)) static int
fuse_vnop_create(struct vop_create_args *ap)
{
	struct vnode *dvp = ap->a_dvp;
	struct vnode **vpp = ap->a_vpp;
	struct componentname *cnp = ap->a_cnp;
	struct vattr *vap = ap->a_vap;
	struct thread *td = cnp->cn_thread;
	struct ucred *cred = cnp->cn_cred;

	struct fuse_data *data;
	struct fuse_create_in *fci;
	struct fuse_entry_out *feo;
	struct fuse_open_out *foo;
	struct fuse_dispatcher fdi, fdi2;
	struct fuse_dispatcher *fdip = &fdi;
	struct fuse_dispatcher *fdip2 = NULL;

	int err;

	struct mount *mp = vnode_mount(dvp);
	data = fuse_get_mpdata(mp);
	uint64_t parentnid = VTOFUD(dvp)->nid;
	mode_t mode = MAKEIMODE(vap->va_type, vap->va_mode);
	enum fuse_opcode op;
	int flags;

	if (fuse_isdeadfs(dvp))
		return ENXIO;

	/* FUSE expects sockets to be created with FUSE_MKNOD */
	if (vap->va_type == VSOCK)
		return fuse_internal_mknod(dvp, vpp, cnp, vap);

	/* 
	 * VOP_CREATE doesn't tell us the open(2) flags, so we guess.  Only a
	 * writable mode makes sense, and we might as well include readability
	 * too.
	 */
	flags = O_RDWR;

	bzero(&fdi, sizeof(fdi));

	if (vap->va_type != VREG)
		return (EINVAL);

	if (!fsess_isimpl(mp, FUSE_CREATE) || vap->va_type == VSOCK) {
		/* Fallback to FUSE_MKNOD/FUSE_OPEN */
		fdisp_make_mknod_for_fallback(fdip, cnp, dvp, parentnid, td,
			cred, mode, &op);
	} else {
		/* Use FUSE_CREATE */
		size_t insize;

		op = FUSE_CREATE;
		fdisp_init(fdip, sizeof(*fci) + cnp->cn_namelen + 1);
		fdisp_make(fdip, op, vnode_mount(dvp), parentnid, td, cred);
		fci = fdip->indata;
		fci->mode = mode;
		fci->flags = O_CREAT | flags;
		if (fuse_libabi_geq(data, 7, 12)) {
			insize = sizeof(*fci);
			fci->umask = td->td_proc->p_fd->fd_cmask;
		} else {
			insize = sizeof(struct fuse_open_in);
		}

		memcpy((char *)fdip->indata + insize, cnp->cn_nameptr,
		    cnp->cn_namelen);
		((char *)fdip->indata)[insize + cnp->cn_namelen] = '\0';
	}

	err = fdisp_wait_answ(fdip);

	if (err) {
		if (err == ENOSYS && op == FUSE_CREATE) {
			fsess_set_notimpl(mp, FUSE_CREATE);
			fdisp_destroy(fdip);
			fdisp_make_mknod_for_fallback(fdip, cnp, dvp,
				parentnid, td, cred, mode, &op);
			err = fdisp_wait_answ(fdip);
		}
		if (err)
			goto out;
	}

	feo = fdip->answ;

	if ((err = fuse_internal_checkentry(feo, vap->va_type))) {
		goto out;
	}

	if (op == FUSE_CREATE) {
		foo = (struct fuse_open_out*)(feo + 1);
	} else {
		/* Issue a separate FUSE_OPEN */
		struct fuse_open_in *foi;

		fdip2 = &fdi2;
		fdisp_init(fdip2, sizeof(*foi));
		fdisp_make(fdip2, FUSE_OPEN, vnode_mount(dvp), feo->nodeid, td,
			cred);
		foi = fdip2->indata;
		foi->flags = flags;
		err = fdisp_wait_answ(fdip2);
		if (err)
			goto out;
		foo = fdip2->answ;
	}
	err = fuse_vnode_get(mp, feo, feo->nodeid, dvp, vpp, cnp, vap->va_type);
	if (err) {
		struct fuse_release_in *fri;
		uint64_t nodeid = feo->nodeid;
		uint64_t fh_id = foo->fh;

		fdisp_init(fdip, sizeof(*fri));
		fdisp_make(fdip, FUSE_RELEASE, mp, nodeid, td, cred);
		fri = fdip->indata;
		fri->fh = fh_id;
		fri->flags = flags;
		fuse_insert_callback(fdip->tick, fuse_internal_forget_callback);
		fuse_insert_message(fdip->tick, false);
		goto out;
	}
	ASSERT_VOP_ELOCKED(*vpp, "fuse_vnop_create");
	fuse_internal_cache_attrs(*vpp, &feo->attr, feo->attr_valid,
		feo->attr_valid_nsec, NULL);

	fuse_filehandle_init(*vpp, FUFH_RDWR, NULL, td, cred, foo);
	fuse_vnode_open(*vpp, foo->open_flags, td);
	/* 
	 * Purge the parent's attribute cache because the daemon should've
	 * updated its mtime and ctime
	 */
	fuse_vnode_clear_attr_cache(dvp);
	cache_purge_negative(dvp);

out:
	if (fdip2)
		fdisp_destroy(fdip2);
	fdisp_destroy(fdip);
	return err;
}