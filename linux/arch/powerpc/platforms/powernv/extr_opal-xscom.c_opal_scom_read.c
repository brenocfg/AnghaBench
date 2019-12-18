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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int u64 ;
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ __pa (int /*<<< orphan*/ *) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int opal_scom_unmangle (int) ; 
 scalar_t__ opal_xscom_read (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opal_scom_read(uint32_t chip, uint64_t addr, u64 reg, u64 *value)
{
	int64_t rc;
	__be64 v;

	reg = opal_scom_unmangle(addr + reg);
	rc = opal_xscom_read(chip, reg, (__be64 *)__pa(&v));
	if (rc) {
		*value = 0xfffffffffffffffful;
		return -EIO;
	}
	*value = be64_to_cpu(v);
	return 0;
}