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
struct thread {int /*<<< orphan*/  td_ucred; } ;
struct shmfd {scalar_t__ shm_refs; } ;
struct shm_rename_args {int flags; int /*<<< orphan*/  path_to; int /*<<< orphan*/  path_from; } ;
typedef  int /*<<< orphan*/  Fnv32_t ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  FNV1_32_INIT ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/  M_SHMFD ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int SHM_RENAME_EXCHANGE ; 
 int SHM_RENAME_NOREPLACE ; 
 int copyinstr (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fnv_32_str (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 char* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_dict_lock ; 
 int /*<<< orphan*/  shm_drop (struct shmfd*) ; 
 int /*<<< orphan*/  shm_hold (struct shmfd*) ; 
 int /*<<< orphan*/  shm_insert (char*,int /*<<< orphan*/ ,struct shmfd*) ; 
 struct shmfd* shm_lookup (char*,int /*<<< orphan*/ ) ; 
 int shm_remove (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

int
sys_shm_rename(struct thread *td, struct shm_rename_args *uap)
{
	char *path_from = NULL, *path_to = NULL;
	Fnv32_t fnv_from, fnv_to;
	struct shmfd *fd_from;
	struct shmfd *fd_to;
	int error;
	int flags;

	flags = uap->flags;

	/*
	 * Make sure the user passed only valid flags.
	 * If you add a new flag, please add a new term here.
	 */
	if ((flags & ~(
	    SHM_RENAME_NOREPLACE |
	    SHM_RENAME_EXCHANGE
	    )) != 0) {
		error = EINVAL;
		goto out;
	}

	/*
	 * EXCHANGE and NOREPLACE don't quite make sense together. Let's
	 * force the user to choose one or the other.
	 */
	if ((flags & SHM_RENAME_NOREPLACE) != 0 &&
	    (flags & SHM_RENAME_EXCHANGE) != 0) {
		error = EINVAL;
		goto out;
	}

	/*
	 * Malloc zone M_SHMFD, since this path may end up freed later from
	 * M_SHMFD if we end up doing an insert.
	 */
	path_from = malloc(MAXPATHLEN, M_SHMFD, M_WAITOK);
	error = copyinstr(uap->path_from, path_from, MAXPATHLEN, NULL);
	if (error)
		goto out;

	path_to = malloc(MAXPATHLEN, M_SHMFD, M_WAITOK);
	error = copyinstr(uap->path_to, path_to, MAXPATHLEN, NULL);
	if (error)
		goto out;

	/* Rename with from/to equal is a no-op */
	if (strncmp(path_from, path_to, MAXPATHLEN) == 0)
		goto out;

	fnv_from = fnv_32_str(path_from, FNV1_32_INIT);
	fnv_to = fnv_32_str(path_to, FNV1_32_INIT);

	sx_xlock(&shm_dict_lock);

	fd_from = shm_lookup(path_from, fnv_from);
	if (fd_from == NULL) {
		sx_xunlock(&shm_dict_lock);
		error = ENOENT;
		goto out;
	}

	fd_to = shm_lookup(path_to, fnv_to);
	if ((flags & SHM_RENAME_NOREPLACE) != 0 && fd_to != NULL) {
		sx_xunlock(&shm_dict_lock);
		error = EEXIST;
		goto out;
	}

	/*
	 * Unconditionally prevents shm_remove from invalidating the 'from'
	 * shm's state.
	 */
	shm_hold(fd_from);
	error = shm_remove(path_from, fnv_from, td->td_ucred);

	/*
	 * One of my assumptions failed if ENOENT (e.g. locking didn't
	 * protect us)
	 */
	KASSERT(error != ENOENT, ("Our shm disappeared during shm_rename: %s",
	    path_from));
	if (error) {
		shm_drop(fd_from);
		sx_xunlock(&shm_dict_lock);
		goto out;
	}

	/*
	 * If we are exchanging, we need to ensure the shm_remove below
	 * doesn't invalidate the dest shm's state.
	 */
	if ((flags & SHM_RENAME_EXCHANGE) != 0 && fd_to != NULL)
		shm_hold(fd_to);

	/*
	 * NOTE: if path_to is not already in the hash, c'est la vie;
	 * it simply means we have nothing already at path_to to unlink.
	 * That is the ENOENT case.
	 *
	 * If we somehow don't have access to unlink this guy, but
	 * did for the shm at path_from, then relink the shm to path_from
	 * and abort with EACCES.
	 *
	 * All other errors: that is weird; let's relink and abort the
	 * operation.
	 */
	error = shm_remove(path_to, fnv_to, td->td_ucred);
	if (error && error != ENOENT) {
		shm_insert(path_from, fnv_from, fd_from);
		shm_drop(fd_from);
		/* Don't free path_from now, since the hash references it */
		path_from = NULL;
		sx_xunlock(&shm_dict_lock);
		goto out;
	}

	shm_insert(path_to, fnv_to, fd_from);

	/* Don't free path_to now, since the hash references it */
	path_to = NULL;

	/* We kept a ref when we removed, and incremented again in insert */
	shm_drop(fd_from);
#ifdef DEBUG
	KASSERT(fd_from->shm_refs > 0, ("Expected >0 refs; got: %d\n",
	    fd_from->shm_refs));
#endif

	if ((flags & SHM_RENAME_EXCHANGE) != 0 && fd_to != NULL) {
		shm_insert(path_from, fnv_from, fd_to);
		path_from = NULL;
		shm_drop(fd_to);
#ifdef DEBUG
		KASSERT(fd_to->shm_refs > 0, ("Expected >0 refs; got: %d\n",
		    fd_to->shm_refs));
#endif
	}

	error = 0;
	sx_xunlock(&shm_dict_lock);

out:
	if (path_from != NULL)
		free(path_from, M_SHMFD);
	if (path_to != NULL)
		free(path_to, M_SHMFD);
	return(error);
}