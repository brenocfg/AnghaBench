#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vnode {TYPE_3__* v_mount; } ;
struct vattr {scalar_t__ va_uid; scalar_t__ va_gid; int va_mode; int va_type; } ;
struct ucred {scalar_t__ cr_uid; scalar_t__ cr_ruid; scalar_t__ cr_svuid; scalar_t__ cr_rgid; scalar_t__ cr_svgid; int cr_ngroups; scalar_t__* cr_groups; TYPE_1__* cr_prison; } ;
struct TYPE_9__ {int mbo_flags; scalar_t__ mbo_uid_max; scalar_t__ mbo_uid_min; int mbo_neg; scalar_t__ mbo_gid_max; scalar_t__ mbo_gid_min; int mbo_type; int /*<<< orphan*/  mbo_fsid; } ;
struct TYPE_10__ {int mbs_flags; scalar_t__ mbs_uid_max; scalar_t__ mbs_uid_min; int mbs_neg; scalar_t__ mbs_gid_max; scalar_t__ mbs_gid_min; scalar_t__ mbs_prison; } ;
struct mac_bsdextended_rule {int mbr_mode; TYPE_4__ mbr_object; TYPE_5__ mbr_subject; } ;
struct TYPE_7__ {int /*<<< orphan*/  f_fsid; } ;
struct TYPE_8__ {TYPE_2__ mnt_stat; } ;
struct TYPE_6__ {scalar_t__ pr_id; } ;

/* Variables and functions */
 int EACCES ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  LOG_AUTHPRIV ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int MBI_ADMIN ; 
 int MBI_EXEC ; 
 int MBI_READ ; 
 int MBI_STAT ; 
 int MBI_WRITE ; 
 int MBO_FSID_DEFINED ; 
 int MBO_GID_DEFINED ; 
 int MBO_GID_SUBJECT ; 
 int MBO_SGID ; 
 int MBO_SUID ; 
 int MBO_TYPE_BLK ; 
 int MBO_TYPE_CHR ; 
 int MBO_TYPE_DEFINED ; 
 int MBO_TYPE_DIR ; 
 int MBO_TYPE_FIFO ; 
 int MBO_TYPE_LNK ; 
 int MBO_TYPE_REG ; 
 int MBO_TYPE_SOCK ; 
 int MBO_UID_DEFINED ; 
 int MBO_UID_SUBJECT ; 
 int MBS_GID_DEFINED ; 
 int MBS_PRISON_DEFINED ; 
 int MBS_UID_DEFINED ; 
 int /*<<< orphan*/  PRIV_VFS_ADMIN ; 
 int /*<<< orphan*/  PRIV_VFS_EXEC ; 
 int /*<<< orphan*/  PRIV_VFS_LOOKUP ; 
 int /*<<< orphan*/  PRIV_VFS_READ ; 
 int /*<<< orphan*/  PRIV_VFS_STAT ; 
 int /*<<< orphan*/  PRIV_VFS_WRITE ; 
 int S_ISGID ; 
 int S_ISUID ; 
#define  VBLK 134 
#define  VCHR 133 
#define  VDIR 132 
#define  VFIFO 131 
#define  VLNK 130 
#define  VREG 129 
#define  VSOCK 128 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ groupmember (scalar_t__,struct ucred*) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ priv_check_cred (struct ucred*,int /*<<< orphan*/ ) ; 
 scalar_t__ ugidfw_firstmatch_enabled ; 
 scalar_t__ ugidfw_logging ; 
 int /*<<< orphan*/  ugidfw_mtx ; 

__attribute__((used)) static int
ugidfw_rulecheck(struct mac_bsdextended_rule *rule,
    struct ucred *cred, struct vnode *vp, struct vattr *vap, int acc_mode)
{
	int mac_granted, match, priv_granted;
	int i;

	/*
	 * Is there a subject match?
	 */
	mtx_assert(&ugidfw_mtx, MA_OWNED);
	if (rule->mbr_subject.mbs_flags & MBS_UID_DEFINED) {
		match =  ((cred->cr_uid <= rule->mbr_subject.mbs_uid_max &&
		    cred->cr_uid >= rule->mbr_subject.mbs_uid_min) ||
		    (cred->cr_ruid <= rule->mbr_subject.mbs_uid_max &&
		    cred->cr_ruid >= rule->mbr_subject.mbs_uid_min) ||
		    (cred->cr_svuid <= rule->mbr_subject.mbs_uid_max &&
		    cred->cr_svuid >= rule->mbr_subject.mbs_uid_min));
		if (rule->mbr_subject.mbs_neg & MBS_UID_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_subject.mbs_flags & MBS_GID_DEFINED) {
		match = ((cred->cr_rgid <= rule->mbr_subject.mbs_gid_max &&
		    cred->cr_rgid >= rule->mbr_subject.mbs_gid_min) ||
		    (cred->cr_svgid <= rule->mbr_subject.mbs_gid_max &&
		    cred->cr_svgid >= rule->mbr_subject.mbs_gid_min));
		if (!match) {
			for (i = 0; i < cred->cr_ngroups; i++) {
				if (cred->cr_groups[i]
				    <= rule->mbr_subject.mbs_gid_max &&
				    cred->cr_groups[i]
				    >= rule->mbr_subject.mbs_gid_min) {
					match = 1;
					break;
				}
			}
		}
		if (rule->mbr_subject.mbs_neg & MBS_GID_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_subject.mbs_flags & MBS_PRISON_DEFINED) {
		match =
		    (cred->cr_prison->pr_id == rule->mbr_subject.mbs_prison);
		if (rule->mbr_subject.mbs_neg & MBS_PRISON_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	/*
	 * Is there an object match?
	 */
	if (rule->mbr_object.mbo_flags & MBO_UID_DEFINED) {
		match = (vap->va_uid <= rule->mbr_object.mbo_uid_max &&
		    vap->va_uid >= rule->mbr_object.mbo_uid_min);
		if (rule->mbr_object.mbo_neg & MBO_UID_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_GID_DEFINED) {
		match = (vap->va_gid <= rule->mbr_object.mbo_gid_max &&
		    vap->va_gid >= rule->mbr_object.mbo_gid_min);
		if (rule->mbr_object.mbo_neg & MBO_GID_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_FSID_DEFINED) {
		match = (bcmp(&(vp->v_mount->mnt_stat.f_fsid),
		    &(rule->mbr_object.mbo_fsid),
		    sizeof(rule->mbr_object.mbo_fsid)) == 0);
		if (rule->mbr_object.mbo_neg & MBO_FSID_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_SUID) {
		match = (vap->va_mode & S_ISUID);
		if (rule->mbr_object.mbo_neg & MBO_SUID)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_SGID) {
		match = (vap->va_mode & S_ISGID);
		if (rule->mbr_object.mbo_neg & MBO_SGID)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_UID_SUBJECT) {
		match = (vap->va_uid == cred->cr_uid ||
		    vap->va_uid == cred->cr_ruid ||
		    vap->va_uid == cred->cr_svuid);
		if (rule->mbr_object.mbo_neg & MBO_UID_SUBJECT)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_GID_SUBJECT) {
		match = (groupmember(vap->va_gid, cred) ||
		    vap->va_gid == cred->cr_rgid ||
		    vap->va_gid == cred->cr_svgid);
		if (rule->mbr_object.mbo_neg & MBO_GID_SUBJECT)
			match = !match;
		if (!match)
			return (0);
	}

	if (rule->mbr_object.mbo_flags & MBO_TYPE_DEFINED) {
		switch (vap->va_type) {
		case VREG:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_REG);
			break;
		case VDIR:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_DIR);
			break;
		case VBLK:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_BLK);
			break;
		case VCHR:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_CHR);
			break;
		case VLNK:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_LNK);
			break;
		case VSOCK:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_SOCK);
			break;
		case VFIFO:
			match = (rule->mbr_object.mbo_type & MBO_TYPE_FIFO);
			break;
		default:
			match = 0;
		}
		if (rule->mbr_object.mbo_neg & MBO_TYPE_DEFINED)
			match = !match;
		if (!match)
			return (0);
	}

	/*
	 * MBI_APPEND should not be here as it should get converted to
	 * MBI_WRITE.
	 */
	priv_granted = 0;
	mac_granted = rule->mbr_mode;
	if ((acc_mode & MBI_ADMIN) && (mac_granted & MBI_ADMIN) == 0 &&
	    priv_check_cred(cred, PRIV_VFS_ADMIN) == 0)
		priv_granted |= MBI_ADMIN;
	if ((acc_mode & MBI_EXEC) && (mac_granted & MBI_EXEC) == 0 &&
	    priv_check_cred(cred, (vap->va_type == VDIR) ? PRIV_VFS_LOOKUP : PRIV_VFS_EXEC) == 0)
		priv_granted |= MBI_EXEC;
	if ((acc_mode & MBI_READ) && (mac_granted & MBI_READ) == 0 &&
	    priv_check_cred(cred, PRIV_VFS_READ) == 0)
		priv_granted |= MBI_READ;
	if ((acc_mode & MBI_STAT) && (mac_granted & MBI_STAT) == 0 &&
	    priv_check_cred(cred, PRIV_VFS_STAT) == 0)
		priv_granted |= MBI_STAT;
	if ((acc_mode & MBI_WRITE) && (mac_granted & MBI_WRITE) == 0 &&
	    priv_check_cred(cred, PRIV_VFS_WRITE) == 0)
		priv_granted |= MBI_WRITE;
	/*
	 * Is the access permitted?
	 */
	if (((mac_granted | priv_granted) & acc_mode) != acc_mode) {
		if (ugidfw_logging)
			log(LOG_AUTHPRIV, "mac_bsdextended: %d:%d request %d"
			    " on %d:%d failed. \n", cred->cr_ruid,
			    cred->cr_rgid, acc_mode, vap->va_uid,
			    vap->va_gid);
		return (EACCES);
	}

	/*
	 * If the rule matched, permits access, and first match is enabled,
	 * return success.
	 */
	if (ugidfw_firstmatch_enabled)
		return (EJUSTRETURN);
	else
		return (0);
}