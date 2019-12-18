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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;
struct e752x_pvt {int* map; } ;

/* Variables and functions */
 scalar_t__ E752X_DRB ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static void e752x_init_mem_map_table(struct pci_dev *pdev,
				struct e752x_pvt *pvt)
{
	int index;
	u8 value, last, row;

	last = 0;
	row = 0;

	for (index = 0; index < 8; index += 2) {
		pci_read_config_byte(pdev, E752X_DRB + index, &value);
		/* test if there is a dimm in this slot */
		if (value == last) {
			/* no dimm in the slot, so flag it as empty */
			pvt->map[index] = 0xff;
			pvt->map[index + 1] = 0xff;
		} else {	/* there is a dimm in the slot */
			pvt->map[index] = row;
			row++;
			last = value;
			/* test the next value to see if the dimm is double
			 * sided
			 */
			pci_read_config_byte(pdev, E752X_DRB + index + 1,
					&value);

			/* the dimm is single sided, so flag as empty */
			/* this is a double sided dimm to save the next row #*/
			pvt->map[index + 1] = (value == last) ? 0xff :	row;
			row++;
			last = value;
		}
	}
}