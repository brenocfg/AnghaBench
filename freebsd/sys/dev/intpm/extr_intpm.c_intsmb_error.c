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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PIIX4_SMBHSTSTAT_BUSC ; 
 int PIIX4_SMBHSTSTAT_ERR ; 
 int PIIX4_SMBHSTSTAT_FAIL ; 
 int SMB_EABORT ; 
 int SMB_ECOLLI ; 
 int SMB_ENOACK ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int
intsmb_error(device_t dev, int status)
{
	int error = 0;

	/*
	 * PIIX4_SMBHSTSTAT_ERR can mean either of
	 * - SMB_ENOACK ("Unclaimed cycle"),
	 * - SMB_ETIMEOUT ("Host device time-out"),
	 * - SMB_EINVAL ("Illegal command field").
	 * SMB_ENOACK seems to be most typical.
	 */
	if (status & PIIX4_SMBHSTSTAT_ERR)
		error |= SMB_ENOACK;
	if (status & PIIX4_SMBHSTSTAT_BUSC)
		error |= SMB_ECOLLI;
	if (status & PIIX4_SMBHSTSTAT_FAIL)
		error |= SMB_EABORT;

	if (error != 0 && bootverbose)
		device_printf(dev, "error = %d, status = %#x\n", error, status);

	return (error);
}