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
typedef  unsigned int u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 scalar_t__ AE_NOT_CONFIGURED ; 
 size_t EINVAL ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
 scalar_t__ acpi_acquire_global_lock (int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  acpi_release_global_lock (unsigned int) ; 
 int /*<<< orphan*/  fw_cfg_dev_lock ; 
 int /*<<< orphan*/  fw_cfg_reg_data ; 
 int /*<<< orphan*/  fw_cfg_sel_endianness (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread8_rep (int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t fw_cfg_read_blob(u16 key,
				void *buf, loff_t pos, size_t count)
{
	u32 glk = -1U;
	acpi_status status;

	/* If we have ACPI, ensure mutual exclusion against any potential
	 * device access by the firmware, e.g. via AML methods:
	 */
	status = acpi_acquire_global_lock(ACPI_WAIT_FOREVER, &glk);
	if (ACPI_FAILURE(status) && status != AE_NOT_CONFIGURED) {
		/* Should never get here */
		WARN(1, "fw_cfg_read_blob: Failed to lock ACPI!\n");
		memset(buf, 0, count);
		return -EINVAL;
	}

	mutex_lock(&fw_cfg_dev_lock);
	fw_cfg_sel_endianness(key);
	while (pos-- > 0)
		ioread8(fw_cfg_reg_data);
	ioread8_rep(fw_cfg_reg_data, buf, count);
	mutex_unlock(&fw_cfg_dev_lock);

	acpi_release_global_lock(glk);
	return count;
}