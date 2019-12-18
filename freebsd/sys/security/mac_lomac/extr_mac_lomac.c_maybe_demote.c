#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct vnode {TYPE_3__* v_mount; } ;
struct vattr {scalar_t__ va_fileid; } ;
struct sbuf {int dummy; } ;
struct proc {int /*<<< orphan*/  p_comm; int /*<<< orphan*/  p_pid; TYPE_1__* p_pgrp; int /*<<< orphan*/  p_label; } ;
struct mac_lomac {int ml_flags; int /*<<< orphan*/  ml_single; int /*<<< orphan*/  ml_rangehigh; int /*<<< orphan*/  ml_rangelow; } ;
struct mac_lomac_proc {struct mac_lomac mac_lomac; int /*<<< orphan*/  mtx; } ;
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_12__ {int /*<<< orphan*/  cr_uid; } ;
struct TYPE_11__ {int td_flags; TYPE_7__* td_ucred; struct proc* td_proc; } ;
struct TYPE_9__ {int /*<<< orphan*/  f_mntonname; } ;
struct TYPE_10__ {TYPE_2__ mnt_stat; } ;
struct TYPE_8__ {int /*<<< orphan*/  pg_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO ; 
 int MAC_LOMAC_FLAG_UPDATE ; 
 struct mac_lomac_proc* PSLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SBUF_AUTOEXTEND ; 
 int TDF_ASTPENDING ; 
 int TDF_MACPEND ; 
 scalar_t__ VOP_GETATTR (struct vnode*,struct vattr*,TYPE_7__*) ; 
 int /*<<< orphan*/  bzero (struct mac_lomac*,int) ; 
 TYPE_4__* curthread ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char*,char const*,...) ; 
 int /*<<< orphan*/  lomac_copy_range (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_copy_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_dominate_element (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lomac_dominate_single (struct mac_lomac*,struct mac_lomac*) ; 
 int /*<<< orphan*/  lomac_to_string (struct sbuf*,struct mac_lomac*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 char* sbuf_data (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_delete (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_finish (struct sbuf*) ; 
 int /*<<< orphan*/  sbuf_new (struct sbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (TYPE_4__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_4__*) ; 

__attribute__((used)) static int
maybe_demote(struct mac_lomac *subjlabel, struct mac_lomac *objlabel,
    const char *actionname, const char *objname, struct vnode *vp)
{
	struct sbuf subjlabel_sb, subjtext_sb, objlabel_sb;
	char *subjlabeltext, *objlabeltext, *subjtext;
	struct mac_lomac cached_subjlabel;
	struct mac_lomac_proc *subj;
	struct vattr va;
	struct proc *p;
	pid_t pgid;

	subj = PSLOT(curthread->td_proc->p_label);

	p = curthread->td_proc;
	mtx_lock(&subj->mtx);
        if (subj->mac_lomac.ml_flags & MAC_LOMAC_FLAG_UPDATE) {
		/*
		 * Check to see if the pending demotion would be more or less
		 * severe than this one, and keep the more severe.  This can
		 * only happen for a multi-threaded application.
		 */
		if (lomac_dominate_single(objlabel, &subj->mac_lomac)) {
			mtx_unlock(&subj->mtx);
			return (0);
		}
	}
	bzero(&subj->mac_lomac, sizeof(subj->mac_lomac));
	/*
	 * Always demote the single label.
	 */
	lomac_copy_single(objlabel, &subj->mac_lomac);
	/*
	 * Start with the original range, then minimize each side of the
	 * range to the point of not dominating the object.  The high side
	 * will always be demoted, of course.
	 */
	lomac_copy_range(subjlabel, &subj->mac_lomac);
	if (!lomac_dominate_element(&objlabel->ml_single,
	    &subj->mac_lomac.ml_rangelow))
		subj->mac_lomac.ml_rangelow = objlabel->ml_single;
	subj->mac_lomac.ml_rangehigh = objlabel->ml_single;
	subj->mac_lomac.ml_flags |= MAC_LOMAC_FLAG_UPDATE;
	thread_lock(curthread);
	curthread->td_flags |= TDF_ASTPENDING | TDF_MACPEND;
	thread_unlock(curthread);

	/*
	 * Avoid memory allocation while holding a mutex; cache the label.
	 */
	lomac_copy_single(&subj->mac_lomac, &cached_subjlabel);
	mtx_unlock(&subj->mtx);

	sbuf_new(&subjlabel_sb, NULL, 0, SBUF_AUTOEXTEND);
	lomac_to_string(&subjlabel_sb, subjlabel);
	sbuf_finish(&subjlabel_sb);
	subjlabeltext = sbuf_data(&subjlabel_sb);

	sbuf_new(&subjtext_sb, NULL, 0, SBUF_AUTOEXTEND);
	lomac_to_string(&subjtext_sb, &subj->mac_lomac);
	sbuf_finish(&subjtext_sb);
	subjtext = sbuf_data(&subjtext_sb);

	sbuf_new(&objlabel_sb, NULL, 0, SBUF_AUTOEXTEND);
	lomac_to_string(&objlabel_sb, objlabel);
	sbuf_finish(&objlabel_sb);
	objlabeltext = sbuf_data(&objlabel_sb);

	pgid = p->p_pgrp->pg_id;		/* XXX could be stale? */
	if (vp != NULL && VOP_GETATTR(vp, &va, curthread->td_ucred) == 0) {
		log(LOG_INFO, "LOMAC: level-%s subject p%dg%du%d:%s demoted to"
		    " level %s after %s a level-%s %s (inode=%ju, "
		    "mountpount=%s)\n",
		    subjlabeltext, p->p_pid, pgid, curthread->td_ucred->cr_uid,
		    p->p_comm, subjtext, actionname, objlabeltext, objname,
		    (uintmax_t)va.va_fileid, vp->v_mount->mnt_stat.f_mntonname);
	} else {
		log(LOG_INFO, "LOMAC: level-%s subject p%dg%du%d:%s demoted to"
		    " level %s after %s a level-%s %s\n",
		    subjlabeltext, p->p_pid, pgid, curthread->td_ucred->cr_uid,
		    p->p_comm, subjtext, actionname, objlabeltext, objname);
	}

	sbuf_delete(&subjlabel_sb);
	sbuf_delete(&subjtext_sb);
	sbuf_delete(&objlabel_sb);
		
	return (0);
}