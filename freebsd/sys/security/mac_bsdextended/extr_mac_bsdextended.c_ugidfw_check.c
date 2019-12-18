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
struct vattr {int dummy; } ;
struct ucred {int dummy; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int MBI_APPEND ; 
 int MBI_WRITE ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int rule_slots ; 
 int /*<<< orphan*/ ** rules ; 
 int /*<<< orphan*/  ugidfw_mtx ; 
 int ugidfw_rulecheck (int /*<<< orphan*/ *,struct ucred*,struct vnode*,struct vattr*,int) ; 

int
ugidfw_check(struct ucred *cred, struct vnode *vp, struct vattr *vap,
    int acc_mode)
{
	int error, i;

	/*
	 * Since we do not separately handle append, map append to write.
	 */
	if (acc_mode & MBI_APPEND) {
		acc_mode &= ~MBI_APPEND;
		acc_mode |= MBI_WRITE;
	}
	mtx_lock(&ugidfw_mtx);
	for (i = 0; i < rule_slots; i++) {
		if (rules[i] == NULL)
			continue;
		error = ugidfw_rulecheck(rules[i], cred,
		    vp, vap, acc_mode);
		if (error == EJUSTRETURN)
			break;
		if (error) {
			mtx_unlock(&ugidfw_mtx);
			return (error);
		}
	}
	mtx_unlock(&ugidfw_mtx);
	return (0);
}