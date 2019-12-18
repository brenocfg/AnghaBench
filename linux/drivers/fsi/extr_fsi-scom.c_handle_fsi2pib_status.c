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
typedef  int uint32_t ;
struct scom_device {int /*<<< orphan*/  fsi_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int EPERM ; 
 int /*<<< orphan*/  SCOM_FSI2PIB_RESET_REG ; 
 int SCOM_STATUS_PARITY ; 
 int SCOM_STATUS_PIB_ABORT ; 
 int SCOM_STATUS_PROTECTION ; 
 int /*<<< orphan*/  fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int handle_fsi2pib_status(struct scom_device *scom, uint32_t status)
{
	uint32_t dummy = -1;

	if (status & SCOM_STATUS_PROTECTION)
		return -EPERM;
	if (status & SCOM_STATUS_PARITY) {
		fsi_device_write(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG, &dummy,
				 sizeof(uint32_t));
		return -EIO;
	}
	/* Return -EBUSY on PIB abort to force a retry */
	if (status & SCOM_STATUS_PIB_ABORT)
		return -EBUSY;
	return 0;
}