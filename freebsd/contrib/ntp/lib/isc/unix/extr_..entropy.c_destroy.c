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
typedef  int /*<<< orphan*/  isc_mem_t ;
struct TYPE_8__ {int type; } ;
typedef  TYPE_1__ isc_entropysource_t ;
struct TYPE_9__ {scalar_t__ refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  pool; int /*<<< orphan*/ * mctx; int /*<<< orphan*/  sources; } ;
typedef  TYPE_2__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
#define  ENTROPY_SOURCETYPE_FILE 129 
#define  ENTROPY_SOURCETYPE_USOCKET 128 
 int ISC_LIST_EMPTY (int /*<<< orphan*/ ) ; 
 TYPE_1__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroysource (TYPE_1__**) ; 
 int /*<<< orphan*/  isc_entropypool_invalidate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_detach (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
destroy(isc_entropy_t **entp) {
	isc_entropy_t *ent;
	isc_entropysource_t *source;
	isc_mem_t *mctx;

	REQUIRE(entp != NULL && *entp != NULL);
	ent = *entp;
	*entp = NULL;

	LOCK(&ent->lock);

	REQUIRE(ent->refcnt == 0);

	/*
	 * Here, detach non-sample sources.
	 */
	source = ISC_LIST_HEAD(ent->sources);
	while (source != NULL) {
		switch(source->type) {
		case ENTROPY_SOURCETYPE_FILE:
		case ENTROPY_SOURCETYPE_USOCKET:
			destroysource(&source);
			break;
		}
		source = ISC_LIST_HEAD(ent->sources);
	}

	/*
	 * If there are other types of sources, we've found a bug.
	 */
	REQUIRE(ISC_LIST_EMPTY(ent->sources));

	mctx = ent->mctx;

	isc_entropypool_invalidate(&ent->pool);

	UNLOCK(&ent->lock);

	DESTROYLOCK(&ent->lock);

	memset(ent, 0, sizeof(isc_entropy_t));
	isc_mem_put(mctx, ent, sizeof(isc_entropy_t));
	isc_mem_detach(&mctx);
}