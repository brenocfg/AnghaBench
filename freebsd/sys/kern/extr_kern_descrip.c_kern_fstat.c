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
struct thread {int /*<<< orphan*/  td_ucred; int /*<<< orphan*/  td_proc; } ;
struct stat {scalar_t__ st_btim_ext; scalar_t__ st_ctim_ext; scalar_t__ st_mtim_ext; scalar_t__ st_atim_ext; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_FD (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_FILE (int /*<<< orphan*/ ,struct file*) ; 
 scalar_t__ KTRPOINT (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_STRUCT ; 
 int /*<<< orphan*/  cap_fstat_rights ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int fget (struct thread*,int,int /*<<< orphan*/ *,struct file**) ; 
 int fo_stat (struct file*,struct stat*,int /*<<< orphan*/ ,struct thread*) ; 
 int /*<<< orphan*/  ktrstat (struct stat*) ; 

int
kern_fstat(struct thread *td, int fd, struct stat *sbp)
{
	struct file *fp;
	int error;

	AUDIT_ARG_FD(fd);

	error = fget(td, fd, &cap_fstat_rights, &fp);
	if (error != 0)
		return (error);

	AUDIT_ARG_FILE(td->td_proc, fp);

	error = fo_stat(fp, sbp, td->td_ucred, td);
	fdrop(fp, td);
#ifdef __STAT_TIME_T_EXT
	if (error == 0) {
		sbp->st_atim_ext = 0;
		sbp->st_mtim_ext = 0;
		sbp->st_ctim_ext = 0;
		sbp->st_btim_ext = 0;
	}
#endif
#ifdef KTRACE
	if (error == 0 && KTRPOINT(td, KTR_STRUCT))
		ktrstat(sbp);
#endif
	return (error);
}