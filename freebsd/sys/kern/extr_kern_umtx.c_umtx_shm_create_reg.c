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
struct umtx_shm_reg {int ushm_refcnt; int ushm_flags; int /*<<< orphan*/  ushm_obj; int /*<<< orphan*/  ushm_cred; int /*<<< orphan*/  ushm_key; } ;
struct TYPE_3__ {int /*<<< orphan*/  object; } ;
struct TYPE_4__ {TYPE_1__ shared; } ;
struct umtx_key {size_t hash; TYPE_2__ info; } ;
struct ucred {int /*<<< orphan*/  cr_ruidinfo; } ;
struct thread {struct ucred* td_ucred; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ ,struct umtx_shm_reg*,int /*<<< orphan*/ ) ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RLIMIT_UMTXP ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct umtx_shm_reg*,int /*<<< orphan*/ ) ; 
 int USHMF_OBJ_LINKED ; 
 int USHMF_REG_LINKED ; 
 int /*<<< orphan*/  USHM_OBJ_UMTX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (struct umtx_key const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  chgumtxcnt (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (struct ucred*) ; 
 int /*<<< orphan*/  lim_cur (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shm_alloc (struct ucred*,int /*<<< orphan*/ ) ; 
 int shm_dotruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct umtx_shm_reg* uma_zalloc (int /*<<< orphan*/ ,int) ; 
 struct umtx_shm_reg* umtx_shm_find_reg (struct umtx_key const*) ; 
 struct umtx_shm_reg* umtx_shm_find_reg_locked (struct umtx_key const*) ; 
 int /*<<< orphan*/  umtx_shm_free_reg (struct umtx_shm_reg*) ; 
 int /*<<< orphan*/  umtx_shm_lock ; 
 int /*<<< orphan*/  umtx_shm_reg_zone ; 
 int /*<<< orphan*/ * umtx_shm_registry ; 
 int /*<<< orphan*/  ushm_obj_link ; 
 int /*<<< orphan*/  ushm_reg_link ; 

__attribute__((used)) static int
umtx_shm_create_reg(struct thread *td, const struct umtx_key *key,
    struct umtx_shm_reg **res)
{
	struct umtx_shm_reg *reg, *reg1;
	struct ucred *cred;
	int error;

	reg = umtx_shm_find_reg(key);
	if (reg != NULL) {
		*res = reg;
		return (0);
	}
	cred = td->td_ucred;
	if (!chgumtxcnt(cred->cr_ruidinfo, 1, lim_cur(td, RLIMIT_UMTXP)))
		return (ENOMEM);
	reg = uma_zalloc(umtx_shm_reg_zone, M_WAITOK | M_ZERO);
	reg->ushm_refcnt = 1;
	bcopy(key, &reg->ushm_key, sizeof(*key));
	reg->ushm_obj = shm_alloc(td->td_ucred, O_RDWR);
	reg->ushm_cred = crhold(cred);
	error = shm_dotruncate(reg->ushm_obj, PAGE_SIZE);
	if (error != 0) {
		umtx_shm_free_reg(reg);
		return (error);
	}
	mtx_lock(&umtx_shm_lock);
	reg1 = umtx_shm_find_reg_locked(key);
	if (reg1 != NULL) {
		mtx_unlock(&umtx_shm_lock);
		umtx_shm_free_reg(reg);
		*res = reg1;
		return (0);
	}
	reg->ushm_refcnt++;
	TAILQ_INSERT_TAIL(&umtx_shm_registry[key->hash], reg, ushm_reg_link);
	LIST_INSERT_HEAD(USHM_OBJ_UMTX(key->info.shared.object), reg,
	    ushm_obj_link);
	reg->ushm_flags = USHMF_REG_LINKED | USHMF_OBJ_LINKED;
	mtx_unlock(&umtx_shm_lock);
	*res = reg;
	return (0);
}