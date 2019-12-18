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
struct shmfd {int shm_mode; char* shm_path; int /*<<< orphan*/  shm_size; } ;
struct TYPE_6__ {int kf_file_mode; int /*<<< orphan*/  kf_file_size; } ;
struct TYPE_7__ {TYPE_1__ kf_file; } ;
struct kinfo_file {int /*<<< orphan*/  kf_path; TYPE_2__ kf_un; int /*<<< orphan*/  kf_type; } ;
struct TYPE_10__ {TYPE_4__* td_ucred; } ;
struct TYPE_9__ {TYPE_3__* cr_prison; } ;
struct TYPE_8__ {char* pr_path; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  KF_TYPE_SHM ; 
 int /*<<< orphan*/  SA_LOCKED ; 
 int S_IFREG ; 
 TYPE_5__* curthread ; 
 int /*<<< orphan*/  shm_dict_lock ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,size_t) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
shm_fill_kinfo_locked(struct shmfd *shmfd, struct kinfo_file *kif, bool list)
{
	const char *path, *pr_path;
	size_t pr_pathlen;
	bool visible;

	sx_assert(&shm_dict_lock, SA_LOCKED);
	kif->kf_type = KF_TYPE_SHM;
	kif->kf_un.kf_file.kf_file_mode = S_IFREG | shmfd->shm_mode;
	kif->kf_un.kf_file.kf_file_size = shmfd->shm_size;
	if (shmfd->shm_path != NULL) {
		if (shmfd->shm_path != NULL) {
			path = shmfd->shm_path;
			pr_path = curthread->td_ucred->cr_prison->pr_path;
			if (strcmp(pr_path, "/") != 0) {
				/* Return the jail-rooted pathname. */
				pr_pathlen = strlen(pr_path);
				visible = strncmp(path, pr_path, pr_pathlen)
				    == 0 && path[pr_pathlen] == '/';
				if (list && !visible)
					return (EPERM);
				if (visible)
					path += pr_pathlen;
			}
			strlcpy(kif->kf_path, path, sizeof(kif->kf_path));
		}
	}
	return (0);
}