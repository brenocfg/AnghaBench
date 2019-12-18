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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct ksem {int ks_mode; int /*<<< orphan*/  ks_gid; int /*<<< orphan*/  ks_uid; } ;
struct file {struct ksem* f_data; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int /*<<< orphan*/  VADMIN ; 
 int /*<<< orphan*/  VREG ; 
 int mac_posixsem_check_setmode (struct ucred*,struct ksem*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 
 int vaccess (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ucred*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ksem_chmod(struct file *fp, mode_t mode, struct ucred *active_cred,
    struct thread *td)
{
	struct ksem *ks;
	int error;

	error = 0;
	ks = fp->f_data;
	mtx_lock(&sem_lock);
#ifdef MAC
	error = mac_posixsem_check_setmode(active_cred, ks, mode);
	if (error != 0)
		goto out;
#endif
	error = vaccess(VREG, ks->ks_mode, ks->ks_uid, ks->ks_gid, VADMIN,
	    active_cred, NULL);
	if (error != 0)
		goto out;
	ks->ks_mode = mode & ACCESSPERMS;
out:
	mtx_unlock(&sem_lock);
	return (error);
}