#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_3__* td_ucred; TYPE_1__* td_proc; } ;
struct ksem {int /*<<< orphan*/  ks_flags; } ;
struct filedesc {int fd_cmask; } ;
struct file {int dummy; } ;
typedef  int /*<<< orphan*/  semid_t ;
typedef  int mode_t ;
struct TYPE_8__ {TYPE_2__* cr_prison; } ;
struct TYPE_7__ {char* pr_path; } ;
struct TYPE_6__ {struct filedesc* p_fd; } ;
typedef  int /*<<< orphan*/  Fnv32_t ;

/* Variables and functions */
 int ACCESSPERMS ; 
 int /*<<< orphan*/  AUDIT_ARG_FFLAGS (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_MODE (int) ; 
 int /*<<< orphan*/  AUDIT_ARG_UPATH1_CANON (char*) ; 
 int /*<<< orphan*/  AUDIT_ARG_VALUE (unsigned int) ; 
 int /*<<< orphan*/  DTYPE_SEM ; 
 int EEXIST ; 
 int EINVAL ; 
 int ENFILE ; 
 int ENOENT ; 
 int ENOSPC ; 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KS_ANONYMOUS ; 
 scalar_t__ MAXPATHLEN ; 
 int /*<<< orphan*/  M_KSEM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int O_CREAT ; 
 int O_EXCL ; 
 unsigned int SEM_VALUE_MAX ; 
 int copyinstr (char const*,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int falloc (struct thread*,struct file**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdclose (struct thread*,struct file*,int) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int,int /*<<< orphan*/ ,struct ksem*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnv_32_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int ksem_access (struct ksem*,TYPE_3__*) ; 
 struct ksem* ksem_alloc (TYPE_3__*,int,unsigned int) ; 
 int ksem_create_copyout_semid (struct thread*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ksem_dict_lock ; 
 int /*<<< orphan*/  ksem_hold (struct ksem*) ; 
 int /*<<< orphan*/  ksem_insert (char*,int /*<<< orphan*/ ,struct ksem*) ; 
 struct ksem* ksem_lookup (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ksem_ops ; 
 int mac_posixsem_check_open (TYPE_3__*,struct ksem*) ; 
 char* malloc (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 size_t strlcpy (char*,char const*,scalar_t__) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ksem_create(struct thread *td, const char *name, semid_t *semidp, mode_t mode,
    unsigned int value, int flags, int compat32)
{
	struct filedesc *fdp;
	struct ksem *ks;
	struct file *fp;
	char *path;
	const char *pr_path;
	size_t pr_pathlen;
	Fnv32_t fnv;
	int error, fd;

	AUDIT_ARG_FFLAGS(flags);
	AUDIT_ARG_MODE(mode);
	AUDIT_ARG_VALUE(value);

	if (value > SEM_VALUE_MAX)
		return (EINVAL);

	fdp = td->td_proc->p_fd;
	mode = (mode & ~fdp->fd_cmask) & ACCESSPERMS;
	error = falloc(td, &fp, &fd, O_CLOEXEC);
	if (error) {
		if (name == NULL)
			error = ENOSPC;
		return (error);
	}

	/*
	 * Go ahead and copyout the file descriptor now.  This is a bit
	 * premature, but it is a lot easier to handle errors as opposed
	 * to later when we've possibly created a new semaphore, etc.
	 */
	error = ksem_create_copyout_semid(td, semidp, fd, compat32);
	if (error) {
		fdclose(td, fp, fd);
		fdrop(fp, td);
		return (error);
	}

	if (name == NULL) {
		/* Create an anonymous semaphore. */
		ks = ksem_alloc(td->td_ucred, mode, value);
		if (ks == NULL)
			error = ENOSPC;
		else
			ks->ks_flags |= KS_ANONYMOUS;
	} else {
		path = malloc(MAXPATHLEN, M_KSEM, M_WAITOK);
		pr_path = td->td_ucred->cr_prison->pr_path;

		/* Construct a full pathname for jailed callers. */
		pr_pathlen = strcmp(pr_path, "/") == 0 ? 0
		    : strlcpy(path, pr_path, MAXPATHLEN);
		error = copyinstr(name, path + pr_pathlen,
		    MAXPATHLEN - pr_pathlen, NULL);

		/* Require paths to start with a '/' character. */
		if (error == 0 && path[pr_pathlen] != '/')
			error = EINVAL;
		if (error) {
			fdclose(td, fp, fd);
			fdrop(fp, td);
			free(path, M_KSEM);
			return (error);
		}

		AUDIT_ARG_UPATH1_CANON(path);
		fnv = fnv_32_str(path, FNV1_32_INIT);
		sx_xlock(&ksem_dict_lock);
		ks = ksem_lookup(path, fnv);
		if (ks == NULL) {
			/* Object does not exist, create it if requested. */
			if (flags & O_CREAT) {
				ks = ksem_alloc(td->td_ucred, mode, value);
				if (ks == NULL)
					error = ENFILE;
				else {
					ksem_insert(path, fnv, ks);
					path = NULL;
				}
			} else
				error = ENOENT;
		} else {
			/*
			 * Object already exists, obtain a new
			 * reference if requested and permitted.
			 */
			if ((flags & (O_CREAT | O_EXCL)) ==
			    (O_CREAT | O_EXCL))
				error = EEXIST;
			else {
#ifdef MAC
				error = mac_posixsem_check_open(td->td_ucred,
				    ks);
				if (error == 0)
#endif
				error = ksem_access(ks, td->td_ucred);
			}
			if (error == 0)
				ksem_hold(ks);
#ifdef INVARIANTS
			else
				ks = NULL;
#endif
		}
		sx_xunlock(&ksem_dict_lock);
		if (path)
			free(path, M_KSEM);
	}

	if (error) {
		KASSERT(ks == NULL, ("ksem_create error with a ksem"));
		fdclose(td, fp, fd);
		fdrop(fp, td);
		return (error);
	}
	KASSERT(ks != NULL, ("ksem_create w/o a ksem"));

	finit(fp, FREAD | FWRITE, DTYPE_SEM, ks, &ksem_ops);

	fdrop(fp, td);

	return (0);
}