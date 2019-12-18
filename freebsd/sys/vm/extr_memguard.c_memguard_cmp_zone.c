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
struct TYPE_3__ {int uz_flags; int /*<<< orphan*/  uz_name; int /*<<< orphan*/  uz_size; } ;

/* Variables and functions */
 int MG_GUARD_NOFREE ; 
 int UMA_ZONE_NOFREE ; 
 scalar_t__ memguard_cmp (int /*<<< orphan*/ ) ; 
 int memguard_options ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_memguard_desc ; 

int
memguard_cmp_zone(uma_zone_t zone)
{

	if ((memguard_options & MG_GUARD_NOFREE) == 0 &&
	    zone->uz_flags & UMA_ZONE_NOFREE)
		return (0);

	if (memguard_cmp(zone->uz_size))
		return (1);

	/*
	 * The safest way of comparsion is to always compare zone name,
	 * but it is also the slowest way.
	 */
	return (strcmp(zone->uz_name, vm_memguard_desc) == 0);
}