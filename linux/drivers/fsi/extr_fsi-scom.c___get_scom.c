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
typedef  int uint64_t ;
typedef  int uint32_t ;
struct scom_device {int /*<<< orphan*/  fsi_dev; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  SCOM_CMD_REG ; 
 int /*<<< orphan*/  SCOM_DATA0_REG ; 
 int /*<<< orphan*/  SCOM_DATA1_REG ; 
 int SCOM_READ_CMD ; 
 int /*<<< orphan*/  SCOM_STATUS_REG ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int fsi_device_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int fsi_device_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int __get_scom(struct scom_device *scom_dev, uint64_t *value,
		      uint32_t addr, uint32_t *status)
{
	__be32 data, raw_status;
	int rc;


	*value = 0ULL;
	data = cpu_to_be32(SCOM_READ_CMD | addr);
	rc = fsi_device_write(scom_dev->fsi_dev, SCOM_CMD_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;
	rc = fsi_device_read(scom_dev->fsi_dev, SCOM_STATUS_REG, &raw_status,
			     sizeof(uint32_t));
	if (rc)
		return rc;

	/*
	 * Read the data registers even on error, so we don't have
	 * to interpret the status register here.
	 */
	rc = fsi_device_read(scom_dev->fsi_dev, SCOM_DATA0_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;
	*value |= (uint64_t)be32_to_cpu(data) << 32;
	rc = fsi_device_read(scom_dev->fsi_dev, SCOM_DATA1_REG, &data,
				sizeof(uint32_t));
	if (rc)
		return rc;
	*value |= be32_to_cpu(data);
	*status = be32_to_cpu(raw_status);

	return rc;
}