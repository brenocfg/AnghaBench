#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ core_unit; } ;
struct TYPE_4__ {TYPE_1__ match; } ;
struct bhnd_core_match {TYPE_2__ m; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_devclass_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_MATCH_CORE_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_MATCH_CORE_UNIT (int) ; 
 int /*<<< orphan*/  bhnd_bus_match_child (int /*<<< orphan*/ ,struct bhnd_core_match*) ; 

device_t
bhnd_bus_find_child(device_t bus, bhnd_devclass_t class, int unit)
{
	struct bhnd_core_match md = {
		BHND_MATCH_CORE_CLASS(class),
		BHND_MATCH_CORE_UNIT(unit)
	};

	if (unit == -1)
		md.m.match.core_unit = 0;

	return bhnd_bus_match_child(bus, &md);
}