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
struct ksem {int ks_mode; char* ks_path; int /*<<< orphan*/  ks_value; } ;
struct TYPE_6__ {int kf_sem_mode; int /*<<< orphan*/  kf_sem_value; } ;
struct TYPE_7__ {TYPE_1__ kf_sem; } ;
struct kinfo_file {int /*<<< orphan*/  kf_path; TYPE_2__ kf_un; int /*<<< orphan*/  kf_type; } ;
struct filedesc {int dummy; } ;
struct file {struct ksem* f_data; } ;
struct TYPE_10__ {TYPE_4__* td_ucred; } ;
struct TYPE_9__ {TYPE_3__* cr_prison; } ;
struct TYPE_8__ {char* pr_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  KF_TYPE_SEM ; 
 int S_IFREG ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  ksem_dict_lock ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_lock ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ksem_fill_kinfo(struct file *fp, struct kinfo_file *kif, struct filedesc *fdp)
{
	const char *path, *pr_path;
	struct ksem *ks;
	size_t pr_pathlen;

	kif->kf_type = KF_TYPE_SEM;
	ks = fp->f_data;
	mtx_lock(&sem_lock);
	kif->kf_un.kf_sem.kf_sem_value = ks->ks_value;
	kif->kf_un.kf_sem.kf_sem_mode = S_IFREG | ks->ks_mode;	/* XXX */
	mtx_unlock(&sem_lock);
	if (ks->ks_path != NULL) {
		sx_slock(&ksem_dict_lock);
		if (ks->ks_path != NULL) {
			path = ks->ks_path;
			pr_path = curthread->td_ucred->cr_prison->pr_path;
			if (strcmp(pr_path, "/") != 0) {
				/* Return the jail-rooted pathname. */
				pr_pathlen = strlen(pr_path);
				if (strncmp(path, pr_path, pr_pathlen) == 0 &&
				    path[pr_pathlen] == '/')
					path += pr_pathlen;
			}
			strlcpy(kif->kf_path, path, sizeof(kif->kf_path));
		}
		sx_sunlock(&ksem_dict_lock);
	}
	return (0);
}