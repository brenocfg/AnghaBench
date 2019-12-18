#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct aper_size_info_lvl2 {int size; int /*<<< orphan*/  size_value; } ;
struct TYPE_6__ {int aperture_size_idx; void* current_size; void* previous_size; TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  gart_addr_ofs; } ;
struct TYPE_4__ {int num_aperture_sizes; int /*<<< orphan*/  aperture_sizes; } ;

/* Variables and functions */
 struct aper_size_info_lvl2* A_SIZE_LVL2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SVWRKS_SIZE_MASK ; 
 TYPE_3__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ serverworks_private ; 

__attribute__((used)) static int serverworks_fetch_size(void)
{
	int i;
	u32 temp;
	u32 temp2;
	struct aper_size_info_lvl2 *values;

	values = A_SIZE_LVL2(agp_bridge->driver->aperture_sizes);
	pci_read_config_dword(agp_bridge->dev,serverworks_private.gart_addr_ofs,&temp);
	pci_write_config_dword(agp_bridge->dev,serverworks_private.gart_addr_ofs,
					SVWRKS_SIZE_MASK);
	pci_read_config_dword(agp_bridge->dev,serverworks_private.gart_addr_ofs,&temp2);
	pci_write_config_dword(agp_bridge->dev,serverworks_private.gart_addr_ofs,temp);
	temp2 &= SVWRKS_SIZE_MASK;

	for (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) {
		if (temp2 == values[i].size_value) {
			agp_bridge->previous_size =
			    agp_bridge->current_size = (void *) (values + i);

			agp_bridge->aperture_size_idx = i;
			return values[i].size;
		}
	}

	return 0;
}