#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  int /*<<< orphan*/ * uma_slab_t ;
typedef  int /*<<< orphan*/ * uma_keg_t ;
struct TYPE_4__ {int /*<<< orphan*/ * uz_keg; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEG_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KEG_UNLOCK (int /*<<< orphan*/ *) ; 
 int M_NOVM ; 
 int M_NOWAIT ; 
 int /*<<< orphan*/ * keg_fetch_slab (int /*<<< orphan*/ *,TYPE_1__*,int,int) ; 

__attribute__((used)) static uma_slab_t
zone_fetch_slab(uma_zone_t zone, uma_keg_t keg, int domain, int flags)
{
	uma_slab_t slab;

	if (keg == NULL) {
		keg = zone->uz_keg;
		KEG_LOCK(keg);
	}

	for (;;) {
		slab = keg_fetch_slab(keg, zone, domain, flags);
		if (slab)
			return (slab);
		if (flags & (M_NOWAIT | M_NOVM))
			break;
	}
	KEG_UNLOCK(keg);
	return (NULL);
}