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
typedef  int UINT32 ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int HCI_FAN_SHIFT ; 
 int HCI_GET ; 
 int /*<<< orphan*/  HCI_REG_FAN ; 
 int HCI_SET ; 
 int hci_call (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static int
hci_force_fan(ACPI_HANDLE h, int op, UINT32 *state)
{
	int		ret;

	ACPI_SERIAL_ASSERT(toshiba);
	if (op == HCI_SET) {
		if (*state > 1)
			return (EINVAL);
		*state <<= HCI_FAN_SHIFT;
	}
	ret = hci_call(h, op, HCI_REG_FAN, state);
	if (ret == 0 && op == HCI_GET)
		*state >>= HCI_FAN_SHIFT;
	return (ret);
}