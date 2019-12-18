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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct scom_device {int /*<<< orphan*/  fsi_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENODEV ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  SCOM_FSI2PIB_RESET_REG ; 
#define  SCOM_PIB_BAD_ADDR 133 
 int SCOM_PIB_BLOCKED ; 
#define  SCOM_PIB_CLK_ERR 132 
#define  SCOM_PIB_OFFLINE 131 
#define  SCOM_PIB_PARITY_ERR 130 
#define  SCOM_PIB_PARTIAL 129 
 int SCOM_PIB_SUCCESS ; 
#define  SCOM_PIB_TIMEOUT 128 
 int /*<<< orphan*/  fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int handle_pib_status(struct scom_device *scom, uint8_t status)
{
	uint32_t dummy = -1;

	if (status == SCOM_PIB_SUCCESS)
		return 0;
	if (status == SCOM_PIB_BLOCKED)
		return -EBUSY;

	/* Reset the bridge */
	fsi_device_write(scom->fsi_dev, SCOM_FSI2PIB_RESET_REG, &dummy,
			 sizeof(uint32_t));

	switch(status) {
	case SCOM_PIB_OFFLINE:
		return -ENODEV;
	case SCOM_PIB_BAD_ADDR:
		return -ENXIO;
	case SCOM_PIB_TIMEOUT:
		return -ETIMEDOUT;
	case SCOM_PIB_PARTIAL:
	case SCOM_PIB_CLK_ERR:
	case SCOM_PIB_PARITY_ERR:
	default:
		return -EIO;
	}
}