#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct stm32_cryp {int /*<<< orphan*/  dev; int /*<<< orphan*/  gcm_ctr; TYPE_1__* areq; } ;
struct TYPE_2__ {int /*<<< orphan*/  iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYP_CR ; 
 int CR_CRYPEN ; 
 int CR_PH_INIT ; 
 int /*<<< orphan*/  GCM_CTR_INIT ; 
 int cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stm32_cryp_hw_write_iv (struct stm32_cryp*,int*) ; 
 int stm32_cryp_wait_enable (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_cryp_gcm_init(struct stm32_cryp *cryp, u32 cfg)
{
	int ret;
	u32 iv[4];

	/* Phase 1 : init */
	memcpy(iv, cryp->areq->iv, 12);
	iv[3] = cpu_to_be32(GCM_CTR_INIT);
	cryp->gcm_ctr = GCM_CTR_INIT;
	stm32_cryp_hw_write_iv(cryp, iv);

	stm32_cryp_write(cryp, CRYP_CR, cfg | CR_PH_INIT | CR_CRYPEN);

	/* Wait for end of processing */
	ret = stm32_cryp_wait_enable(cryp);
	if (ret)
		dev_err(cryp->dev, "Timeout (gcm init)\n");

	return ret;
}