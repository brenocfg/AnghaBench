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
struct umtxq_chain {int /*<<< orphan*/  uc_pi_list; } ;
struct umtx_pi {scalar_t__ pi_refcount; int /*<<< orphan*/  pi_blocked; int /*<<< orphan*/ * pi_owner; int /*<<< orphan*/  pi_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct umtx_pi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UMTXQ_LOCKED_ASSERT (struct umtxq_chain*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pi_hashlink ; 
 int /*<<< orphan*/  umtx_lock ; 
 int /*<<< orphan*/  umtx_pi_disown (struct umtx_pi*) ; 
 int /*<<< orphan*/  umtx_pi_free (struct umtx_pi*) ; 
 struct umtxq_chain* umtxq_getchain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
umtx_pi_unref(struct umtx_pi *pi)
{
	struct umtxq_chain *uc;

	uc = umtxq_getchain(&pi->pi_key);
	UMTXQ_LOCKED_ASSERT(uc);
	KASSERT(pi->pi_refcount > 0, ("invalid reference count"));
	if (--pi->pi_refcount == 0) {
		mtx_lock(&umtx_lock);
		if (pi->pi_owner != NULL)
			umtx_pi_disown(pi);
		KASSERT(TAILQ_EMPTY(&pi->pi_blocked),
			("blocked queue not empty"));
		mtx_unlock(&umtx_lock);
		TAILQ_REMOVE(&uc->uc_pi_list, pi, pi_hashlink);
		umtx_pi_free(pi);
	}
}