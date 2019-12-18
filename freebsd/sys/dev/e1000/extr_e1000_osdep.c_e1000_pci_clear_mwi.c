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
struct e1000_osdep {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int pci_cmd_word; } ;
struct e1000_hw {TYPE_1__ bus; scalar_t__ back; } ;

/* Variables and functions */
 int CMD_MEM_WRT_INVALIDATE ; 
 int /*<<< orphan*/  PCIR_COMMAND ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void
e1000_pci_clear_mwi(struct e1000_hw *hw)
{
	pci_write_config(((struct e1000_osdep *)hw->back)->dev, PCIR_COMMAND,
	    (hw->bus.pci_cmd_word & ~CMD_MEM_WRT_INVALIDATE), 2);
}