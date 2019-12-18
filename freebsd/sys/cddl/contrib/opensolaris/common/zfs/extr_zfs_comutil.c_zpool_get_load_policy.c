#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int zlp_rewind; void* zlp_maxdata; void* zlp_maxmeta; void* zlp_txg; } ;
typedef  TYPE_1__ zpool_load_policy_t ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 void* UINT64_MAX ; 
 int /*<<< orphan*/  ZPOOL_LOAD_DATA_THRESH ; 
 int /*<<< orphan*/  ZPOOL_LOAD_META_THRESH ; 
 int /*<<< orphan*/  ZPOOL_LOAD_POLICY ; 
 int /*<<< orphan*/  ZPOOL_LOAD_REQUEST_TXG ; 
 int /*<<< orphan*/  ZPOOL_LOAD_REWIND_POLICY ; 
 void* ZPOOL_NO_REWIND ; 
 int ZPOOL_REWIND_POLICIES ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_value_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ nvpair_value_uint32 (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

void
zpool_get_load_policy(nvlist_t *nvl, zpool_load_policy_t *zlpp)
{
	nvlist_t *policy;
	nvpair_t *elem;
	char *nm;

	/* Defaults */
	zlpp->zlp_rewind = ZPOOL_NO_REWIND;
	zlpp->zlp_maxmeta = 0;
	zlpp->zlp_maxdata = UINT64_MAX;
	zlpp->zlp_txg = UINT64_MAX;

	if (nvl == NULL)
		return;

	elem = NULL;
	while ((elem = nvlist_next_nvpair(nvl, elem)) != NULL) {
		nm = nvpair_name(elem);
		if (strcmp(nm, ZPOOL_LOAD_POLICY) == 0) {
			if (nvpair_value_nvlist(elem, &policy) == 0)
				zpool_get_load_policy(policy, zlpp);
			return;
		} else if (strcmp(nm, ZPOOL_LOAD_REWIND_POLICY) == 0) {
			if (nvpair_value_uint32(elem, &zlpp->zlp_rewind) == 0)
				if (zlpp->zlp_rewind & ~ZPOOL_REWIND_POLICIES)
					zlpp->zlp_rewind = ZPOOL_NO_REWIND;
		} else if (strcmp(nm, ZPOOL_LOAD_REQUEST_TXG) == 0) {
			(void) nvpair_value_uint64(elem, &zlpp->zlp_txg);
		} else if (strcmp(nm, ZPOOL_LOAD_META_THRESH) == 0) {
			(void) nvpair_value_uint64(elem, &zlpp->zlp_maxmeta);
		} else if (strcmp(nm, ZPOOL_LOAD_DATA_THRESH) == 0) {
			(void) nvpair_value_uint64(elem, &zlpp->zlp_maxdata);
		}
	}
	if (zlpp->zlp_rewind == 0)
		zlpp->zlp_rewind = ZPOOL_NO_REWIND;
}