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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int FM_NVA_FREE ; 
 int /*<<< orphan*/  fm_nva_xdestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_lookup_nv_alloc (int /*<<< orphan*/ *) ; 

void
fm_nvlist_destroy(nvlist_t *nvl, int flag)
{
	nv_alloc_t *nva = nvlist_lookup_nv_alloc(nvl);

	nvlist_free(nvl);

	if (nva != NULL) {
		if (flag == FM_NVA_FREE)
			fm_nva_xdestroy(nva);
	}
}