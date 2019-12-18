#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct svc_req {scalar_t__ rq_prog; int rq_vers; struct fha_hash_entry* rq_p1; int /*<<< orphan*/  rq_p3; int /*<<< orphan*/  rq_p2; } ;
struct TYPE_8__ {scalar_t__ enable; } ;
struct fha_callbacks {int dummy; } ;
struct fha_params {TYPE_1__ ctls; struct fha_callbacks callbacks; } ;
struct fha_info {int /*<<< orphan*/  offset; int /*<<< orphan*/  locktype; int /*<<< orphan*/  fh; } ;
struct fha_hash_entry {int /*<<< orphan*/  mtx; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_lock; int /*<<< orphan*/  st_p3; int /*<<< orphan*/  st_p2; } ;
typedef  TYPE_2__ SVCTHREAD ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (TYPE_2__*,char*) ; 
 scalar_t__ NFS_PROG ; 
 int /*<<< orphan*/  fha_extract_info (struct svc_req*,struct fha_info*,struct fha_callbacks*) ; 
 int /*<<< orphan*/  fha_hash_entry_add_op (struct fha_hash_entry*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* fha_hash_entry_choose_thread (struct fha_params*,struct fha_hash_entry*,struct fha_info*,TYPE_2__*) ; 
 struct fha_hash_entry* fha_hash_entry_lookup (struct fha_params*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ ) ; 

SVCTHREAD *
fha_assign(SVCTHREAD *this_thread, struct svc_req *req,
    struct fha_params *softc)
{
	SVCTHREAD *thread;
	struct fha_info i;
	struct fha_hash_entry *fhe;
	struct fha_callbacks *cb;

	cb = &softc->callbacks;

	/* Check to see whether we're enabled. */
	if (softc->ctls.enable == 0)
		goto thist;

	/*
	 * Only do placement if this is an NFS request.
	 */
	if (req->rq_prog != NFS_PROG)
		goto thist;

	if (req->rq_vers != 2 && req->rq_vers != 3)
		goto thist;

	fha_extract_info(req, &i, cb);

	/*
	 * We save the offset associated with this request for later
	 * nfsd matching.
	 */
	fhe = fha_hash_entry_lookup(softc, i.fh);
	req->rq_p1 = fhe;
	req->rq_p2 = i.locktype;
	req->rq_p3 = i.offset;

	/*
	 * Choose a thread, taking into consideration locality, thread load,
	 * and the number of threads already working on this file.
	 */
	thread = fha_hash_entry_choose_thread(softc, fhe, &i, this_thread);
	KASSERT(thread, ("fha_assign: NULL thread!"));
	fha_hash_entry_add_op(fhe, i.locktype, 1);
	thread->st_p2++;
	thread->st_p3 = i.offset;

	/*
	 * Grab the pool lock here to not let chosen thread go away before
	 * the new request inserted to its queue while we drop fhe lock.
	 */
	mtx_lock(&thread->st_lock);
	mtx_unlock(fhe->mtx);

	return (thread);
thist:
	req->rq_p1 = NULL;
	mtx_lock(&this_thread->st_lock);
	return (this_thread);
}