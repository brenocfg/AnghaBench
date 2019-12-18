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
struct TYPE_2__ {scalar_t__ status; scalar_t__ alarm; scalar_t__ done; } ;
union acpi_smb_status {int raw; TYPE_1__ fields; } ;
typedef  int u8 ;
struct acpi_smb_hc {int done; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
#define  ACPI_SBS_BATTERY 130 
#define  ACPI_SBS_CHARGER 129 
#define  ACPI_SBS_MANAGER 128 
 int /*<<< orphan*/  ACPI_SMB_ALARM_ADDRESS ; 
 int /*<<< orphan*/  ACPI_SMB_STATUS ; 
 int /*<<< orphan*/  OSL_NOTIFY_HANDLER ; 
 scalar_t__ SMBUS_OK ; 
 int /*<<< orphan*/  acpi_os_execute (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_smb_hc*) ; 
 int /*<<< orphan*/  acpi_smbus_callback ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ smb_hc_read (struct acpi_smb_hc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smb_hc_write (struct acpi_smb_hc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int smbus_alarm(void *context)
{
	struct acpi_smb_hc *hc = context;
	union acpi_smb_status status;
	u8 address;
	if (smb_hc_read(hc, ACPI_SMB_STATUS, &status.raw))
		return 0;
	/* Check if it is only a completion notify */
	if (status.fields.done && status.fields.status == SMBUS_OK) {
		hc->done = true;
		wake_up(&hc->wait);
	}
	if (!status.fields.alarm)
		return 0;
	mutex_lock(&hc->lock);
	smb_hc_read(hc, ACPI_SMB_ALARM_ADDRESS, &address);
	status.fields.alarm = 0;
	smb_hc_write(hc, ACPI_SMB_STATUS, status.raw);
	/* We are only interested in events coming from known devices */
	switch (address >> 1) {
		case ACPI_SBS_CHARGER:
		case ACPI_SBS_MANAGER:
		case ACPI_SBS_BATTERY:
			acpi_os_execute(OSL_NOTIFY_HANDLER,
					acpi_smbus_callback, hc);
		default:;
	}
	mutex_unlock(&hc->lock);
	return 0;
}