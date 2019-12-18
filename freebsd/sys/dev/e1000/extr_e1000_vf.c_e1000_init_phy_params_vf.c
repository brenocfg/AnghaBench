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
struct TYPE_3__ {int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct TYPE_4__ {TYPE_1__ ops; int /*<<< orphan*/  type; } ;
struct e1000_hw {TYPE_2__ phy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFUNC (char*) ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 int /*<<< orphan*/  e1000_acquire_vf ; 
 int /*<<< orphan*/  e1000_phy_vf ; 
 int /*<<< orphan*/  e1000_release_vf ; 

__attribute__((used)) static s32 e1000_init_phy_params_vf(struct e1000_hw *hw)
{
	DEBUGFUNC("e1000_init_phy_params_vf");
	hw->phy.type = e1000_phy_vf;
	hw->phy.ops.acquire = e1000_acquire_vf;
	hw->phy.ops.release = e1000_release_vf;

	return E1000_SUCCESS;
}