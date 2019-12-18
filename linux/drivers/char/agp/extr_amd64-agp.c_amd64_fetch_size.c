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
typedef  int u32 ;
struct pci_dev {int dummy; } ;
struct aper_size_info_32 {int size_value; int size; } ;
struct TYPE_6__ {int aperture_size_idx; void* current_size; void* previous_size; TYPE_1__* driver; } ;
struct TYPE_5__ {struct pci_dev* misc; } ;
struct TYPE_4__ {int num_aperture_sizes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMD64_GARTAPERTURECTL ; 
 struct aper_size_info_32* A_SIZE_32 (int /*<<< orphan*/ ) ; 
 TYPE_3__* agp_bridge ; 
 int /*<<< orphan*/  amd64_aperture_sizes ; 
 TYPE_2__* node_to_amd_nb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int amd64_fetch_size(void)
{
	struct pci_dev *dev;
	int i;
	u32 temp;
	struct aper_size_info_32 *values;

	dev = node_to_amd_nb(0)->misc;
	if (dev==NULL)
		return 0;

	pci_read_config_dword(dev, AMD64_GARTAPERTURECTL, &temp);
	temp = (temp & 0xe);
	values = A_SIZE_32(amd64_aperture_sizes);

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