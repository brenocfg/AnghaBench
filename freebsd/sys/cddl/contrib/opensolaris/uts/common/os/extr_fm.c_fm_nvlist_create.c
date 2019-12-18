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
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  fm_mem_alloc_ops ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv_alloc_fini (int /*<<< orphan*/ *) ; 
 scalar_t__ nv_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_xalloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

nvlist_t *
fm_nvlist_create(nv_alloc_t *nva)
{
	int hdl_alloced = 0;
	nvlist_t *nvl;
	nv_alloc_t *nvhdl;

	if (nva == NULL) {
		nvhdl = kmem_zalloc(sizeof (nv_alloc_t), KM_SLEEP);

		if (nv_alloc_init(nvhdl, &fm_mem_alloc_ops, NULL, 0) != 0) {
			kmem_free(nvhdl, sizeof (nv_alloc_t));
			return (NULL);
		}
		hdl_alloced = 1;
	} else {
		nvhdl = nva;
	}

	if (nvlist_xalloc(&nvl, NV_UNIQUE_NAME, nvhdl) != 0) {
		if (hdl_alloced) {
			nv_alloc_fini(nvhdl);
			kmem_free(nvhdl, sizeof (nv_alloc_t));
		}
		return (NULL);
	}

	return (nvl);
}