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
typedef  int u32 ;
struct cc_drvdata {int dummy; } ;

/* Variables and functions */
 int CC_FIPS_SYNC_MODULE_OK ; 
 int CC_FIPS_SYNC_TEE_STATUS ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GPR_HOST ; 
 int cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cc_get_tee_fips_status(struct cc_drvdata *drvdata)
{
	u32 reg;

	reg = cc_ioread(drvdata, CC_REG(GPR_HOST));
	/* Did the TEE report status? */
	if (reg & CC_FIPS_SYNC_TEE_STATUS)
		/* Yes. Is it OK? */
		return (reg & CC_FIPS_SYNC_MODULE_OK);

	/* No. It's either not in use or will be reported later */
	return true;
}