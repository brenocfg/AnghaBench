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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  HCI_REG_VIDEO_OUTPUT ; 
 int HCI_SET ; 
 int HCI_VIDEO_OUTPUT_FLAG ; 
 int /*<<< orphan*/  METHOD_VIDEO ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int hci_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  toshiba ; 

__attribute__((used)) static int
hci_video_output(ACPI_HANDLE h, int op, UINT32 *video_output)
{
	int		ret;
	ACPI_STATUS	status;

	ACPI_SERIAL_ASSERT(toshiba);
	if (op == HCI_SET) {
		if (*video_output < 1 || *video_output > 7)
			return (EINVAL);
		if (h == NULL)
			return (ENXIO);
		*video_output |= HCI_VIDEO_OUTPUT_FLAG;
		status = acpi_SetInteger(h, METHOD_VIDEO, *video_output);
		if (ACPI_SUCCESS(status))
			ret = 0;
		else
			ret = ENXIO;
	} else {
		ret = hci_call(h, op, HCI_REG_VIDEO_OUTPUT, video_output);
		if (ret == 0)
			*video_output &= 0xff;
	}

	return (ret);
}