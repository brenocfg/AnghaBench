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
struct cc_drvdata {scalar_t__ hw_rev; } ;

/* Variables and functions */
 int CC_FIPS_SYNC_MODULE_ERROR ; 
 int CC_FIPS_SYNC_MODULE_OK ; 
 int CC_FIPS_SYNC_REE_STATUS ; 
 scalar_t__ CC_HW_REV_712 ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_GPR0 ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int) ; 

void cc_set_ree_fips_status(struct cc_drvdata *drvdata, bool status)
{
	int val = CC_FIPS_SYNC_REE_STATUS;

	if (drvdata->hw_rev < CC_HW_REV_712)
		return;

	val |= (status ? CC_FIPS_SYNC_MODULE_OK : CC_FIPS_SYNC_MODULE_ERROR);

	cc_iowrite(drvdata, CC_REG(HOST_GPR0), val);
}