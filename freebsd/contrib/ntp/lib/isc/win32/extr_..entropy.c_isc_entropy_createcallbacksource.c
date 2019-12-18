#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ isc_result_t ;
typedef  int /*<<< orphan*/  isc_entropystop_t ;
typedef  int /*<<< orphan*/  isc_entropystart_t ;
struct TYPE_16__ {void* arg; int /*<<< orphan*/  stopfunc; int /*<<< orphan*/ * getfunc; int /*<<< orphan*/  startfunc; void* start_called; int /*<<< orphan*/  samplequeue; } ;
struct TYPE_13__ {TYPE_4__ callback; } ;
struct TYPE_14__ {int /*<<< orphan*/  name; scalar_t__ total; TYPE_3__* ent; int /*<<< orphan*/  type; int /*<<< orphan*/  magic; TYPE_1__ sources; void* bad; } ;
typedef  TYPE_2__ isc_entropysource_t ;
typedef  int /*<<< orphan*/ * isc_entropyget_t ;
struct TYPE_15__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  mctx; int /*<<< orphan*/  nsources; int /*<<< orphan*/  sources; } ;
typedef  TYPE_3__ isc_entropy_t ;
typedef  TYPE_4__ isc_cbsource_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENTROPY_SOURCETYPE_CALLBACK ; 
 void* ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LINK_INIT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC_LIST_APPEND (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ISC_R_NOMEMORY ; 
 scalar_t__ ISC_R_SUCCESS ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  SOURCE_MAGIC ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_ENTROPY (TYPE_3__*) ; 
 TYPE_2__* isc_mem_get (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ samplesource_allocate (TYPE_3__*,int /*<<< orphan*/ *) ; 

isc_result_t
isc_entropy_createcallbacksource(isc_entropy_t *ent,
				 isc_entropystart_t start,
				 isc_entropyget_t get,
				 isc_entropystop_t stop,
				 void *arg,
				 isc_entropysource_t **sourcep)
{
	isc_result_t result;
	isc_entropysource_t *source;
	isc_cbsource_t *cbs;

	REQUIRE(VALID_ENTROPY(ent));
	REQUIRE(get != NULL);
	REQUIRE(sourcep != NULL && *sourcep == NULL);

	LOCK(&ent->lock);

	source = isc_mem_get(ent->mctx, sizeof(isc_entropysource_t));
	if (source == NULL) {
		result = ISC_R_NOMEMORY;
		goto errout;
	}
	source->bad = ISC_FALSE;

	cbs = &source->sources.callback;

	result = samplesource_allocate(ent, &cbs->samplequeue);
	if (result != ISC_R_SUCCESS)
		goto errout;

	cbs->start_called = ISC_FALSE;
	cbs->startfunc = start;
	cbs->getfunc = get;
	cbs->stopfunc = stop;
	cbs->arg = arg;

	/*
	 * From here down, no failures can occur.
	 */
	source->magic = SOURCE_MAGIC;
	source->type = ENTROPY_SOURCETYPE_CALLBACK;
	source->ent = ent;
	source->total = 0;
	memset(source->name, 0, sizeof(source->name));
	ISC_LINK_INIT(source, link);

	/*
	 * Hook it into the entropy system.
	 */
	ISC_LIST_APPEND(ent->sources, source, link);
	ent->nsources++;

	*sourcep = source;

	UNLOCK(&ent->lock);
	return (ISC_R_SUCCESS);

 errout:
	if (source != NULL)
		isc_mem_put(ent->mctx, source, sizeof(isc_entropysource_t));

	UNLOCK(&ent->lock);

	return (result);
}