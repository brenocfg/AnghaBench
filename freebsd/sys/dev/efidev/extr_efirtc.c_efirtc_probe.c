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
struct efi_tm {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BUS_PROBE_DEFAULT ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int efi_get_time (struct efi_tm*) ; 

__attribute__((used)) static int
efirtc_probe(device_t dev)
{
	struct efi_tm tm;
	int error;

	/*
	 * Check whether we can read the time.  This will stop us from attaching
	 * when there is EFI Runtime support but the gettime function is
	 * unimplemented, e.g. on some builds of U-Boot.
	 */
	if ((error = efi_get_time(&tm)) != 0) {
		if (bootverbose)
			device_printf(dev, "cannot read EFI realtime clock, "
			    "error %d\n", error);
		return (error);
	}
	device_set_desc(dev, "EFI Realtime Clock");
	return (BUS_PROBE_DEFAULT);
}