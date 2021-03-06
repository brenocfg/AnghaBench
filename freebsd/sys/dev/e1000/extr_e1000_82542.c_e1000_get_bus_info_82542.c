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
struct TYPE_2__ {int /*<<< orphan*/  width; int /*<<< orphan*/  speed; int /*<<< orphan*/  type; } ;
struct e1000_hw {TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_bus_speed_unknown ; 
 int /*<<< orphan*/  e1000_bus_type_pci ; 
 int /*<<< orphan*/  e1000_bus_width_unknown ; 

__attribute__((used)) static s32 e1000_get_bus_info_82542(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_get_bus_info_82542");

	hw->bus.type = e1000_bus_type_pci;
	hw->bus.speed = e1000_bus_speed_unknown;
	hw->bus.width = e1000_bus_width_unknown;

	return E1000_SUCCESS;
}