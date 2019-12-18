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
struct TYPE_2__ {int pes; } ;
struct safexcel_crypto_priv {scalar_t__ version; int /*<<< orphan*/  dev; TYPE_1__ config; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 scalar_t__ EIP197B_MRVL ; 
 scalar_t__ EIP197D_MRVL ; 
 scalar_t__ EIP197_DEVBRD ; 
 scalar_t__ EIP197_PE (struct safexcel_crypto_priv*) ; 
 scalar_t__ EIP197_PE_ICE_RAM_CTRL (int) ; 
 int /*<<< orphan*/  EIP197_PE_ICE_RAM_CTRL_PUE_PROG_EN ; 
 int ENODEV ; 
 size_t FW_IFPP ; 
 size_t FW_IPUE ; 
 int FW_NB ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  eip197_init_firmware (struct safexcel_crypto_priv*) ; 
 scalar_t__ eip197_start_firmware (struct safexcel_crypto_priv*,int,int,int) ; 
 int eip197_write_firmware (struct safexcel_crypto_priv*,struct firmware const*) ; 
 int firmware_request_nowarn (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int eip197_load_firmwares(struct safexcel_crypto_priv *priv)
{
	const char *fw_name[] = {"ifpp.bin", "ipue.bin"};
	const struct firmware *fw[FW_NB];
	char fw_path[37], *dir = NULL;
	int i, j, ret = 0, pe;
	int ipuesz, ifppsz, minifw = 0;

	if (priv->version == EIP197D_MRVL)
		dir = "eip197d";
	else if (priv->version == EIP197B_MRVL ||
		 priv->version == EIP197_DEVBRD)
		dir = "eip197b";
	else
		return -ENODEV;

retry_fw:
	for (i = 0; i < FW_NB; i++) {
		snprintf(fw_path, 37, "inside-secure/%s/%s", dir, fw_name[i]);
		ret = firmware_request_nowarn(&fw[i], fw_path, priv->dev);
		if (ret) {
			if (minifw || priv->version != EIP197B_MRVL)
				goto release_fw;

			/* Fallback to the old firmware location for the
			 * EIP197b.
			 */
			ret = firmware_request_nowarn(&fw[i], fw_name[i],
						      priv->dev);
			if (ret)
				goto release_fw;
		}
	}

	eip197_init_firmware(priv);

	ifppsz = eip197_write_firmware(priv, fw[FW_IFPP]);

	/* Enable access to IPUE program memories */
	for (pe = 0; pe < priv->config.pes; pe++)
		writel(EIP197_PE_ICE_RAM_CTRL_PUE_PROG_EN,
		       EIP197_PE(priv) + EIP197_PE_ICE_RAM_CTRL(pe));

	ipuesz = eip197_write_firmware(priv, fw[FW_IPUE]);

	if (eip197_start_firmware(priv, ipuesz, ifppsz, minifw)) {
		dev_dbg(priv->dev, "Firmware loaded successfully\n");
		return 0;
	}

	ret = -ENODEV;

release_fw:
	for (j = 0; j < i; j++)
		release_firmware(fw[j]);

	if (!minifw) {
		/* Retry with minifw path */
		dev_dbg(priv->dev, "Firmware set not (fully) present or init failed, falling back to BCLA mode\n");
		dir = "eip197_minifw";
		minifw = 1;
		goto retry_fw;
	}

	dev_dbg(priv->dev, "Firmware load failed.\n");

	return ret;
}