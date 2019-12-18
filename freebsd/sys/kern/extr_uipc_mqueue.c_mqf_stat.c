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
struct ucred {int dummy; } ;
struct thread {int dummy; } ;
struct stat {int st_mode; int /*<<< orphan*/  st_gid; int /*<<< orphan*/  st_uid; int /*<<< orphan*/  st_birthtim; int /*<<< orphan*/  st_ctim; int /*<<< orphan*/  st_mtim; int /*<<< orphan*/  st_atim; } ;
struct mqfs_node {int mn_mode; int /*<<< orphan*/  mn_gid; int /*<<< orphan*/  mn_uid; int /*<<< orphan*/  mn_birth; int /*<<< orphan*/  mn_ctime; int /*<<< orphan*/  mn_mtime; int /*<<< orphan*/  mn_atime; } ;
struct file {struct mqfs_node* f_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_lock; } ;

/* Variables and functions */
 int S_IFIFO ; 
 int /*<<< orphan*/  bzero (struct stat*,int) ; 
 TYPE_1__ mqfs_data ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mqf_stat(struct file *fp, struct stat *st, struct ucred *active_cred,
	struct thread *td)
{
	struct mqfs_node *pn = fp->f_data;

	bzero(st, sizeof *st);
	sx_xlock(&mqfs_data.mi_lock);
	st->st_atim = pn->mn_atime;
	st->st_mtim = pn->mn_mtime;
	st->st_ctim = pn->mn_ctime;
	st->st_birthtim = pn->mn_birth;
	st->st_uid = pn->mn_uid;
	st->st_gid = pn->mn_gid;
	st->st_mode = S_IFIFO | pn->mn_mode;
	sx_xunlock(&mqfs_data.mi_lock);
	return (0);
}