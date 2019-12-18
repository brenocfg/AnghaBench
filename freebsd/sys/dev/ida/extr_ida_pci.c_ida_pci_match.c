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
typedef  scalar_t__ u_int32_t ;
struct ida_board {int board; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ IDA_DEVICEID_DEC_SMART ; 
 scalar_t__ IDA_DEVICEID_NCR_53C1510 ; 
 scalar_t__ IDA_DEVICEID_SMART ; 
 struct ida_board* board_id ; 
 scalar_t__ pci_get_devid (int /*<<< orphan*/ ) ; 
 int pci_get_subdevice (int /*<<< orphan*/ ) ; 
 int pci_get_subvendor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ida_board *
ida_pci_match(device_t dev)
{
	int i;
	u_int32_t id, sub_id;

	id = pci_get_devid(dev);
	sub_id = pci_get_subdevice(dev) << 16 | pci_get_subvendor(dev);

	if (id == IDA_DEVICEID_SMART ||
	    id == IDA_DEVICEID_DEC_SMART ||
	    id == IDA_DEVICEID_NCR_53C1510) {
		for (i = 0; board_id[i].board; i++)
			if (board_id[i].board == sub_id)
				return (&board_id[i]);
	}
	return (NULL);
}