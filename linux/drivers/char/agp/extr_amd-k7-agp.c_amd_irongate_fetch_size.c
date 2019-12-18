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
typedef  int u32 ;
struct aper_size_info_lvl2 {int size_value; int size; } ;
struct TYPE_4__ {int aperture_size_idx; void* current_size; void* previous_size; TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int num_aperture_sizes; int /*<<< orphan*/  aperture_sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD_APSIZE ; 
 struct aper_size_info_lvl2* A_SIZE_LVL2 (int /*<<< orphan*/ ) ; 
 TYPE_2__* agp_bridge ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int amd_irongate_fetch_size(void)
{
	int i;
	u32 temp;
	struct aper_size_info_lvl2 *values;

	pci_read_config_dword(agp_bridge->dev, AMD_APSIZE, &temp);
	temp = (temp & 0x0000000e);
	values = A_SIZE_LVL2(agp_bridge->driver->aperture_sizes);
	for (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) {
		if (temp == values[i].size_value) {
			agp_bridge->previous_size =
			    agp_bridge->current_size = (void *) (values + i);

			agp_bridge->aperture_size_idx = i;
			return values[i].size;
		}
	}

	return 0;
}