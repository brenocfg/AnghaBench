#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_2__* td_ucred; } ;
struct shm_unlink_args {int /*<<< orphan*/  path; } ;
struct TYPE_4__ {TYPE_1__* cr_prison; } ;
struct TYPE_3__ {char* pr_path; } ;
typedef  int /*<<< orphan*/  Fnv32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_ARG_UPATH1_CANON (char*) ; 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 scalar_t__ KTRPOINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_NAMEI ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int copyinstr (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  fnv_32_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktrnamei (char*) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_dict_lock ; 
 int shm_remove (char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
sys_shm_unlink(struct thread *td, struct shm_unlink_args *uap)
{
	char *path;
	const char *pr_path;
	size_t pr_pathlen;
	Fnv32_t fnv;
	int error;

	path = malloc(MAXPATHLEN, M_TEMP, M_WAITOK);
	pr_path = td->td_ucred->cr_prison->pr_path;
	pr_pathlen = strcmp(pr_path, "/") == 0 ? 0
	    : strlcpy(path, pr_path, MAXPATHLEN);
	error = copyinstr(uap->path, path + pr_pathlen, MAXPATHLEN - pr_pathlen,
	    NULL);
	if (error) {
		free(path, M_TEMP);
		return (error);
	}
#ifdef KTRACE
	if (KTRPOINT(curthread, KTR_NAMEI))
		ktrnamei(path);
#endif
	AUDIT_ARG_UPATH1_CANON(path);
	fnv = fnv_32_str(path, FNV1_32_INIT);
	sx_xlock(&shm_dict_lock);
	error = shm_remove(path, fnv, td->td_ucred);
	sx_xunlock(&shm_dict_lock);
	free(path, M_TEMP);

	return (error);
}