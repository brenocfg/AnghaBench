#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_5__ {int refcnt; int /*<<< orphan*/  pool; int /*<<< orphan*/  magic; scalar_t__ initcount; scalar_t__ initialized; int /*<<< orphan*/ * mctx; scalar_t__ nsources; int /*<<< orphan*/ * nextsource; int /*<<< orphan*/  sources; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTROPY_MAGIC ; 
 int /*<<< orphan*/  ISC_LIST_INIT (int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_entropypool_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_1__* isc_mem_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ isc_mutex_init (int /*<<< orphan*/ *) ; 

isc_result_t
isc_entropy_create(isc_mem_t *mctx, isc_entropy_t **entp) {
	isc_result_t result;
	isc_entropy_t *ent;

	REQUIRE(mctx != NULL);
	REQUIRE(entp != NULL && *entp == NULL);

	ent = isc_mem_get(mctx, sizeof(isc_entropy_t));
	if (ent == NULL)
		return (ISC_R_NOMEMORY);

	/*
	 * We need a lock.
	 */
	result = isc_mutex_init(&ent->lock);
	if (result != ISC_R_SUCCESS)
		goto errout;

	/*
	 * From here down, no failures will/can occur.
	 */
	ISC_LIST_INIT(ent->sources);
	ent->nextsource = NULL;
	ent->nsources = 0;
	ent->mctx = NULL;
	isc_mem_attach(mctx, &ent->mctx);
	ent->refcnt = 1;
	ent->initialized = 0;
	ent->initcount = 0;
	ent->magic = ENTROPY_MAGIC;

	isc_entropypool_init(&ent->pool);

	*entp = ent;
	return (ISC_R_SUCCESS);

 errout:
	isc_mem_put(mctx, ent, sizeof(isc_entropy_t));

	return (result);
}