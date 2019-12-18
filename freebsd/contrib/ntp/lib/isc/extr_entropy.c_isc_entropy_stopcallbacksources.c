#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ start_called; int /*<<< orphan*/  arg; int /*<<< orphan*/  (* stopfunc ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_11__ {TYPE_4__ callback; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_1__ sources; } ;
typedef  TYPE_2__ isc_entropysource_t ;
struct TYPE_13__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  sources; } ;
typedef  TYPE_3__ isc_entropy_t ;
typedef  TYPE_4__ isc_cbsource_t ;

/* Variables and functions */
 scalar_t__ ENTROPY_SOURCETYPE_CALLBACK ; 
 scalar_t__ ISC_FALSE ; 
 TYPE_2__* ISC_LIST_HEAD (int /*<<< orphan*/ ) ; 
 TYPE_2__* ISC_LIST_NEXT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_ENTROPY (TYPE_3__*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
isc_entropy_stopcallbacksources(isc_entropy_t *ent) {
	isc_entropysource_t *source;
	isc_cbsource_t *cbs;

	REQUIRE(VALID_ENTROPY(ent));

	LOCK(&ent->lock);

	source = ISC_LIST_HEAD(ent->sources);
	while (source != NULL) {
		if (source->type == ENTROPY_SOURCETYPE_CALLBACK) {
			cbs = &source->sources.callback;
			if (cbs->start_called && cbs->stopfunc != NULL) {
				cbs->stopfunc(source, cbs->arg);
				cbs->start_called = ISC_FALSE;
			}
		}

		source = ISC_LIST_NEXT(source, link);
	}

	UNLOCK(&ent->lock);
}