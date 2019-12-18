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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int pes; } ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ EIP197_FW_FPP_READY ; 
 scalar_t__ EIP197_FW_PUE_READY ; 
 int EIP197_FW_START_POLLCNT ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_ICE_SCRATCH_RAM (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static bool poll_fw_ready(struct safexcel_crypto_priv *priv, int fpp)
{
	int pe, pollcnt;
	u32 base, pollofs;

	if (fpp)
		pollofs  = EIP197_FW_FPP_READY;
	else
		pollofs  = EIP197_FW_PUE_READY;

	for (pe = 0; pe < priv->config.pes; pe++) {
		base = EIP197_PE_ICE_SCRATCH_RAM(pe);
		pollcnt = EIP197_FW_START_POLLCNT;
		while (pollcnt &&
		       (readl_relaxed(EIP197_PE(priv) + base +
			      pollofs) != 1)) {
			pollcnt--;
		}
		if (!pollcnt) {
			dev_err(priv->dev, "FW(%d) for PE %d failed to start\n",
				fpp, pe);
			return false;
		}
	}
	return true;
}