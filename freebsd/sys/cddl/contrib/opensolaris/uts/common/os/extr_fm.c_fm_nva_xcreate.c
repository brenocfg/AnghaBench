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
typedef  int /*<<< orphan*/  nv_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ nv_alloc_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  nv_fixed_ops ; 

nv_alloc_t *
fm_nva_xcreate(char *buf, size_t bufsz)
{
	nv_alloc_t *nvhdl = kmem_zalloc(sizeof (nv_alloc_t), KM_SLEEP);

	if (bufsz == 0 || nv_alloc_init(nvhdl, nv_fixed_ops, buf, bufsz) != 0) {
		kmem_free(nvhdl, sizeof (nv_alloc_t));
		return (NULL);
	}

	return (nvhdl);
}