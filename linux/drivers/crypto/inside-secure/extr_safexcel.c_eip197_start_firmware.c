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
struct TYPE_2__ {int pes; } ;
struct safexcel_crypto_priv {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_ICE_FPP_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_PUE_CTRL (int) ; 
 scalar_t__ EIP197_PE_ICE_RAM_CTRL (int) ; 
 int EIP197_PE_ICE_UENG_DEBUG_RESET ; 
 int EIP197_PE_ICE_UENG_INIT_ALIGN_MASK ; 
 int EIP197_PE_ICE_UENG_START_OFFSET (int) ; 
 int /*<<< orphan*/  poll_fw_ready (struct safexcel_crypto_priv*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static bool eip197_start_firmware(struct safexcel_crypto_priv *priv,
				  int ipuesz, int ifppsz, int minifw)
{
	int pe;
	u32 val;

	for (pe = 0; pe < priv->config.pes; pe++) {
		/* Disable access to all program memory */
		writel(0, EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

		/* Start IFPP microengines */
		if (minifw)
			val = 0;
		else
			val = EIP197_PE_ICE_UENG_START_OFFSET((ifppsz - 1) &
					EIP197_PE_ICE_UENG_INIT_ALIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_RESET;
		writel(val, EIP197_PE(priv) + EIP197_PE_ICE_FPP_CTRL(pe));

		/* Start IPUE microengines */
		if (minifw)
			val = 0;
		else
			val = EIP197_PE_ICE_UENG_START_OFFSET((ipuesz - 1) &
					EIP197_PE_ICE_UENG_INIT_ALIGN_MASK) |
				EIP197_PE_ICE_UENG_DEBUG_RESET;
		writel(val, EIP197_PE(priv) + EIP197_PE_ICE_PUE_CTRL(pe));
	}

	/* For miniFW startup, there is no initialization, so always succeed */
	if (minifw)
		return true;

	/* Wait until all the firmwares have properly started up */
	if (!poll_fw_ready(priv, 1))
		return false;
	if (!poll_fw_ready(priv, 0))
		return false;

	return true;
}