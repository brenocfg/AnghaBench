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
struct spi_command {int tx_cmd_sz; int rx_cmd_sz; struct spi_command** rx_cmd; struct spi_command** tx_cmd; } ;
typedef  struct spi_command uint8_t ;
typedef  int /*<<< orphan*/  txBuf ;
struct at45d_mfg_info {int /*<<< orphan*/  ext_id; int /*<<< orphan*/  jedec_id; } ;
typedef  int /*<<< orphan*/  rxBuf ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 struct spi_command MANUFACTURER_ID ; 
 int SPIBUS_TRANSFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spi_command*) ; 
 int /*<<< orphan*/  be16dec (struct spi_command*) ; 
 int /*<<< orphan*/  be32dec (struct spi_command*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct spi_command*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
at45d_get_mfg_info(device_t dev, struct at45d_mfg_info *resp)
{
	uint8_t rxBuf[8], txBuf[8];
	struct spi_command cmd;
	int err;

	memset(&cmd, 0, sizeof(cmd));
	memset(txBuf, 0, sizeof(txBuf));
	memset(rxBuf, 0, sizeof(rxBuf));

	txBuf[0] = MANUFACTURER_ID;
	cmd.tx_cmd = &txBuf;
	cmd.rx_cmd = &rxBuf;
	cmd.tx_cmd_sz = cmd.rx_cmd_sz = 7;
	err = SPIBUS_TRANSFER(device_get_parent(dev), dev, &cmd);
	if (err)
		return (err);

	resp->jedec_id = be32dec(rxBuf + 1);
	resp->ext_id   = be16dec(rxBuf + 5);

	return (0);
}