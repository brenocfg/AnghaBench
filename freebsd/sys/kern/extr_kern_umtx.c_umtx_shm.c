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
typedef  int u_int ;
struct umtx_shm_reg {int /*<<< orphan*/  ushm_obj; } ;
struct umtx_key {int shared; } ;
struct thread {int* td_retval; int /*<<< orphan*/  td_ucred; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTYPE_SHM ; 
 int EINVAL ; 
 int ESRCH ; 
 int /*<<< orphan*/  FFLAGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  O_CLOEXEC ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PROCESS_SHARE ; 
 int /*<<< orphan*/  TYPE_SHM ; 
 int UMTX_SHM_ALIVE ; 
 int UMTX_SHM_CREAT ; 
 int UMTX_SHM_DESTROY ; 
 int UMTX_SHM_LOOKUP ; 
 int __bitcount (int) ; 
 int falloc_caps (struct thread*,struct file**,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdrop (struct file*,struct thread*) ; 
 int /*<<< orphan*/  finit (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mac_posixshm_check_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int shm_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_hold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shm_ops ; 
 int umtx_key_get (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int umtx_shm_alive (struct thread*,void*) ; 
 int umtx_shm_create_reg (struct thread*,struct umtx_key*,struct umtx_shm_reg**) ; 
 struct umtx_shm_reg* umtx_shm_find_reg (struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_shm_unref_reg (struct umtx_shm_reg*,int) ; 

__attribute__((used)) static int
umtx_shm(struct thread *td, void *addr, u_int flags)
{
	struct umtx_key key;
	struct umtx_shm_reg *reg;
	struct file *fp;
	int error, fd;

	if (__bitcount(flags & (UMTX_SHM_CREAT | UMTX_SHM_LOOKUP |
	    UMTX_SHM_DESTROY| UMTX_SHM_ALIVE)) != 1)
		return (EINVAL);
	if ((flags & UMTX_SHM_ALIVE) != 0)
		return (umtx_shm_alive(td, addr));
	error = umtx_key_get(addr, TYPE_SHM, PROCESS_SHARE, &key);
	if (error != 0)
		return (error);
	KASSERT(key.shared == 1, ("non-shared key"));
	if ((flags & UMTX_SHM_CREAT) != 0) {
		error = umtx_shm_create_reg(td, &key, &reg);
	} else {
		reg = umtx_shm_find_reg(&key);
		if (reg == NULL)
			error = ESRCH;
	}
	umtx_key_release(&key);
	if (error != 0)
		return (error);
	KASSERT(reg != NULL, ("no reg"));
	if ((flags & UMTX_SHM_DESTROY) != 0) {
		umtx_shm_unref_reg(reg, true);
	} else {
#if 0
#ifdef MAC
		error = mac_posixshm_check_open(td->td_ucred,
		    reg->ushm_obj, FFLAGS(O_RDWR));
		if (error == 0)
#endif
			error = shm_access(reg->ushm_obj, td->td_ucred,
			    FFLAGS(O_RDWR));
		if (error == 0)
#endif
			error = falloc_caps(td, &fp, &fd, O_CLOEXEC, NULL);
		if (error == 0) {
			shm_hold(reg->ushm_obj);
			finit(fp, FFLAGS(O_RDWR), DTYPE_SHM, reg->ushm_obj,
			    &shm_ops);
			td->td_retval[0] = fd;
			fdrop(fp, td);
		}
	}
	umtx_shm_unref_reg(reg, false);
	return (error);
}