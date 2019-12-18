#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_2__ {size_t nregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* bin_infos ; 
 size_t extent_nfree_get (int /*<<< orphan*/  const*) ; 
 size_t extent_size_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  extent_slab_get (int /*<<< orphan*/  const*) ; 
 size_t extent_szind_get (int /*<<< orphan*/  const*) ; 
 size_t extent_usize_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void const*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void
extent_util_stats_get(tsdn_t *tsdn, const void *ptr,
    size_t *nfree, size_t *nregs, size_t *size) {
	assert(ptr != NULL && nfree != NULL && nregs != NULL && size != NULL);

	const extent_t *extent = iealloc(tsdn, ptr);
	if (unlikely(extent == NULL)) {
		*nfree = *nregs = *size = 0;
		return;
	}

	*size = extent_size_get(extent);
	if (!extent_slab_get(extent)) {
		*nfree = 0;
		*nregs = 1;
	} else {
		*nfree = extent_nfree_get(extent);
		*nregs = bin_infos[extent_szind_get(extent)].nregs;
		assert(*nfree <= *nregs);
		assert(*nfree * extent_usize_get(extent) <= *size);
	}
}