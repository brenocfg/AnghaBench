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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ opal_scom_unmangle (scalar_t__) ; 
 scalar_t__ opal_xscom_write (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int opal_scom_write(uint32_t chip, uint64_t addr, u64 reg, u64 value)
{
	int64_t rc;

	reg = opal_scom_unmangle(addr + reg);
	rc = opal_xscom_write(chip, reg, value);
	if (rc)
		return -EIO;
	return 0;
}