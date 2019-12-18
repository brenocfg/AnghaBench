#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* base; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ block_region ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ munmap (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_memory(block_region *region)
{
    if (region && region->base) {
#if defined(MAP_ANON) && defined(HAVE_MMAP)
        if (munmap(region->base, region->size)) {
            return; /* LCOV_EXCL_LINE */
        }
#else
        free(region->base);
#endif
    }
    free(region);
}