#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  samplequeue; int /*<<< orphan*/  start_called; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* stopfunc ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  samplequeue; } ;
struct TYPE_13__ {TYPE_5__ callback; TYPE_1__ sample; int /*<<< orphan*/  usocket; int /*<<< orphan*/  file; } ;
struct TYPE_14__ {int type; TYPE_2__ sources; int /*<<< orphan*/  bad; TYPE_4__* ent; } ;
typedef  TYPE_3__ isc_entropysource_t ;
struct TYPE_15__ {scalar_t__ nsources; int /*<<< orphan*/  mctx; int /*<<< orphan*/ * nextsource; int /*<<< orphan*/  sources; } ;
typedef  TYPE_4__ isc_entropy_t ;
typedef  TYPE_5__ isc_cbsource_t ;

/* Variables and functions */
#define  ENTROPY_SOURCETYPE_CALLBACK 131 
#define  ENTROPY_SOURCETYPE_FILE 130 
#define  ENTROPY_SOURCETYPE_SAMPLE 129 
#define  ENTROPY_SOURCETYPE_USOCKET 128 
 int /*<<< orphan*/  ISC_FALSE ; 
 int /*<<< orphan*/  ISC_LIST_UNLINK (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  destroyfilesource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroyusocketsource (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  samplequeue_release (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
destroysource(isc_entropysource_t **sourcep) {
	isc_entropysource_t *source;
	isc_entropy_t *ent;
	isc_cbsource_t *cbs;

	source = *sourcep;
	*sourcep = NULL;
	ent = source->ent;

	ISC_LIST_UNLINK(ent->sources, source, link);
	ent->nextsource = NULL;
	REQUIRE(ent->nsources > 0);
	ent->nsources--;

	switch (source->type) {
	case ENTROPY_SOURCETYPE_FILE:
		if (! source->bad)
			destroyfilesource(&source->sources.file);
		break;
	case ENTROPY_SOURCETYPE_USOCKET:
		if (! source->bad)
			destroyusocketsource(&source->sources.usocket);
		break;
	case ENTROPY_SOURCETYPE_SAMPLE:
		samplequeue_release(ent, &source->sources.sample.samplequeue);
		break;
	case ENTROPY_SOURCETYPE_CALLBACK:
		cbs = &source->sources.callback;
		if (cbs->start_called && cbs->stopfunc != NULL) {
			cbs->stopfunc(source, cbs->arg);
			cbs->start_called = ISC_FALSE;
		}
		samplequeue_release(ent, &cbs->samplequeue);
		break;
	}

	memset(source, 0, sizeof(isc_entropysource_t));

	isc_mem_put(ent->mctx, source, sizeof(isc_entropysource_t));
}