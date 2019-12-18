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
typedef  int u32 ;
struct aper_size_info_32 {int size_value; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  previous_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALI_ATTBASE ; 
 int /*<<< orphan*/  ALI_TAGCTRL ; 
 int /*<<< orphan*/  ALI_TLBCTRL ; 
 struct aper_size_info_32* A_SIZE_32 (int /*<<< orphan*/ ) ; 
 TYPE_1__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ali_cleanup(void)
{
	struct aper_size_info_32 *previous_size;
	u32 temp;

	previous_size = A_SIZE_32(agp_bridge->previous_size);

	pci_read_config_dword(agp_bridge->dev, ALI_TLBCTRL, &temp);
// clear tag
	pci_write_config_dword(agp_bridge->dev, ALI_TAGCTRL,
			((temp & 0xffffff00) | 0x00000001|0x00000002));

	pci_read_config_dword(agp_bridge->dev,  ALI_ATTBASE, &temp);
	pci_write_config_dword(agp_bridge->dev, ALI_ATTBASE,
			((temp & 0x00000ff0) | previous_size->size_value));
}