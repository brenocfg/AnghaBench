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
struct vnode {int dummy; } ;
struct thread {int dummy; } ;
struct mount {int dummy; } ;
struct componentname {char* cn_nameptr; int cn_flags; int /*<<< orphan*/  cn_pnbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int EEXIST ; 
 int HASBUF ; 
 struct vnode* NULLVP ; 
 int PCATCH ; 
 int VOP_WHITEOUT (struct vnode*,struct componentname*,int /*<<< orphan*/ ) ; 
 int V_WAIT ; 
 int /*<<< orphan*/  namei_zone ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int unionfs_relookup (struct vnode*,struct vnode**,struct componentname*,struct componentname*,struct thread*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vn_finished_write (struct mount*) ; 
 int vn_start_write (struct vnode*,struct mount**,int) ; 
 int /*<<< orphan*/  vput (struct vnode*) ; 
 int /*<<< orphan*/  vrele (struct vnode*) ; 

int
unionfs_mkwhiteout(struct vnode *dvp, struct componentname *cnp,
		   struct thread *td, char *path)
{
	int		error;
	struct vnode   *wvp;
	struct componentname cn;
	struct mount   *mp;

	if (path == NULL)
		path = cnp->cn_nameptr;

	wvp = NULLVP;
	if ((error = unionfs_relookup(dvp, &wvp, cnp, &cn, td, path, strlen(path), CREATE)))
		return (error);
	if (wvp != NULLVP) {
		if (cn.cn_flags & HASBUF) {
			uma_zfree(namei_zone, cn.cn_pnbuf);
			cn.cn_flags &= ~HASBUF;
		}
		if (dvp == wvp)
			vrele(wvp);
		else
			vput(wvp);

		return (EEXIST);
	}

	if ((error = vn_start_write(dvp, &mp, V_WAIT | PCATCH)))
		goto unionfs_mkwhiteout_free_out;
	error = VOP_WHITEOUT(dvp, &cn, CREATE);

	vn_finished_write(mp);

unionfs_mkwhiteout_free_out:
	if (cn.cn_flags & HASBUF) {
		uma_zfree(namei_zone, cn.cn_pnbuf);
		cn.cn_flags &= ~HASBUF;
	}

	return (error);
}