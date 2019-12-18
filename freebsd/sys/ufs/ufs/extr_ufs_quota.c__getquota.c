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
typedef  int /*<<< orphan*/  u_long ;
struct thread {TYPE_1__* td_ucred; } ;
struct mount {int dummy; } ;
struct dqblk64 {int dummy; } ;
struct dquot {struct dqblk64 dq_dqb; } ;
struct TYPE_2__ {int /*<<< orphan*/  cr_uid; } ;

/* Variables and functions */
 int EINVAL ; 
#define  GRPQUOTA 129 
 struct dquot* NODQUOT ; 
 int /*<<< orphan*/  NULLVP ; 
 int /*<<< orphan*/  PRIV_VFS_GETQUOTA ; 
#define  USRQUOTA 128 
 int /*<<< orphan*/  VFSTOUFS (struct mount*) ; 
 int dqget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct dquot**) ; 
 int /*<<< orphan*/  dqrele (int /*<<< orphan*/ ,struct dquot*) ; 
 int /*<<< orphan*/  groupmember (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unprivileged_get_quota ; 

__attribute__((used)) static int
_getquota(struct thread *td, struct mount *mp, u_long id, int type,
    struct dqblk64 *dqb)
{
	struct dquot *dq;
	int error;

	switch (type) {
	case USRQUOTA:
		if ((td->td_ucred->cr_uid != id) && !unprivileged_get_quota) {
			error = priv_check(td, PRIV_VFS_GETQUOTA);
			if (error)
				return (error);
		}
		break;

	case GRPQUOTA:
		if (!groupmember(id, td->td_ucred) &&
		    !unprivileged_get_quota) {
			error = priv_check(td, PRIV_VFS_GETQUOTA);
			if (error)
				return (error);
		}
		break;

	default:
		return (EINVAL);
	}

	dq = NODQUOT;
	error = dqget(NULLVP, id, VFSTOUFS(mp), type, &dq);
	if (error)
		return (error);
	*dqb = dq->dq_dqb;
	dqrele(NULLVP, dq);
	return (error);
}