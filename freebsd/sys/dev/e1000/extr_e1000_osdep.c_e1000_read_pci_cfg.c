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
struct e1000_osdep {int /*<<< orphan*/  dev; } ;
struct e1000_hw {scalar_t__ back; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void
e1000_read_pci_cfg(struct e1000_hw *hw, u32 reg, u16 *value)
{
	*value = pci_read_config(((struct e1000_osdep *)hw->back)->dev, reg, 2);
}