#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct svc_req {int /*<<< orphan*/  rq_p2; struct fha_hash_entry* rq_p1; } ;
struct mtx {int dummy; } ;
struct fha_hash_entry {scalar_t__ num_rw; scalar_t__ num_exclusive; struct mtx* mtx; } ;
struct TYPE_4__ {scalar_t__ st_p2; } ;
typedef  TYPE_1__ SVCTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  fha_hash_entry_add_op (struct fha_hash_entry*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fha_hash_entry_remove (struct fha_hash_entry*) ; 
 int /*<<< orphan*/  fha_hash_entry_remove_thread (struct fha_hash_entry*,TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_lock (struct mtx*) ; 
 int /*<<< orphan*/  mtx_unlock (struct mtx*) ; 

void
fha_nd_complete(SVCTHREAD *thread, struct svc_req *req)
{
	struct fha_hash_entry *fhe = req->rq_p1;
	struct mtx *mtx;

	/*
	 * This may be called for reqs that didn't go through
	 * fha_assign (e.g. extra NULL ops used for RPCSEC_GSS.
	 */
	if (!fhe)
		return;

	mtx = fhe->mtx;
	mtx_lock(mtx);
	fha_hash_entry_add_op(fhe, req->rq_p2, -1);
	thread->st_p2--;
	KASSERT(thread->st_p2 >= 0, ("Negative request count %d on %p",
	    thread->st_p2, thread));
	if (thread->st_p2 == 0) {
		fha_hash_entry_remove_thread(fhe, thread);
		if (0 == fhe->num_rw + fhe->num_exclusive)
			fha_hash_entry_remove(fhe);
	}
	mtx_unlock(mtx);
}