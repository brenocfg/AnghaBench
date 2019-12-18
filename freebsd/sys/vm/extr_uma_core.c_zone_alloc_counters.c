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
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_3__ {void* uz_fails; void* uz_frees; void* uz_allocs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_WAITOK ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zone_alloc_counters(uma_zone_t zone)
{

	zone->uz_allocs = counter_u64_alloc(M_WAITOK);
	zone->uz_frees = counter_u64_alloc(M_WAITOK);
	zone->uz_fails = counter_u64_alloc(M_WAITOK);
}