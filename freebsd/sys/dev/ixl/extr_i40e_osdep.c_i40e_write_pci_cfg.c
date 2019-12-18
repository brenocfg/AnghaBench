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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct i40e_osdep {int /*<<< orphan*/  dev; } ;
struct i40e_hw {scalar_t__ back; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
i40e_write_pci_cfg(struct i40e_hw *hw, u32 reg, u16 value)
{
        pci_write_config(((struct i40e_osdep *)hw->back)->dev,
            reg, value, 2);
}