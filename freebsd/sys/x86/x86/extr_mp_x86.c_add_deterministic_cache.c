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
struct TYPE_2__ {int present; int id_shift; } ;

/* Variables and functions */
 int MAX_CACHE_LEVELS ; 
 TYPE_1__* caches ; 
 int core_id_shift ; 
 int mask_width (int) ; 
 int pkg_id_shift ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
add_deterministic_cache(int type, int level, int share_count)
{

	if (type == 0)
		return (0);
	if (type > 3) {
		printf("unexpected cache type %d\n", type);
		return (1);
	}
	if (type == 2) /* ignore instruction cache */
		return (1);
	if (level == 0 || level > MAX_CACHE_LEVELS) {
		printf("unexpected cache level %d\n", type);
		return (1);
	}

	if (caches[level - 1].present) {
		printf("WARNING: multiple entries for L%u data cache\n", level);
		printf("%u => %u\n", caches[level - 1].id_shift,
		    mask_width(share_count));
	}
	caches[level - 1].id_shift = mask_width(share_count);
	caches[level - 1].present = 1;

	if (caches[level - 1].id_shift > pkg_id_shift) {
		printf("WARNING: L%u data cache covers more "
		    "APIC IDs than a package (%u > %u)\n", level,
		    caches[level - 1].id_shift, pkg_id_shift);
		caches[level - 1].id_shift = pkg_id_shift;
	}
	if (caches[level - 1].id_shift < core_id_shift) {
		printf("WARNING: L%u data cache covers fewer "
		    "APIC IDs than a core (%u < %u)\n", level,
		    caches[level - 1].id_shift, core_id_shift);
		caches[level - 1].id_shift = core_id_shift;
	}

	return (1);
}