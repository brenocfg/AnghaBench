#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pseudo; int /*<<< orphan*/  entropy; int /*<<< orphan*/  rotate; int /*<<< orphan*/  cursor; } ;
struct TYPE_6__ {int /*<<< orphan*/  initcount; int /*<<< orphan*/  initialized; int /*<<< orphan*/  nextsource; int /*<<< orphan*/  nsources; TYPE_1__ pool; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_2__ isc_entropy_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_MSGSET_ENTROPY ; 
 int /*<<< orphan*/  ISC_MSG_ENTROPYSTATS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_msgcat ; 
 char* isc_msgcat_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
dumpstats(isc_entropy_t *ent, FILE *out) {
	fprintf(out,
		isc_msgcat_get(isc_msgcat, ISC_MSGSET_ENTROPY,
			       ISC_MSG_ENTROPYSTATS,
			       "Entropy pool %p:  refcnt %u cursor %u,"
			       " rotate %u entropy %u pseudo %u nsources %u"
			       " nextsource %p initialized %u initcount %u\n"),
		ent, ent->refcnt,
		ent->pool.cursor, ent->pool.rotate,
		ent->pool.entropy, ent->pool.pseudo,
		ent->nsources, ent->nextsource, ent->initialized,
		ent->initcount);
}