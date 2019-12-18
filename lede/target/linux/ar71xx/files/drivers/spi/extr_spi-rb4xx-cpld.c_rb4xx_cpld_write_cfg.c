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
typedef  int /*<<< orphan*/  t ;
struct spi_transfer {unsigned char* tx_buf; int len; } ;
struct spi_message {int dummy; } ;
struct rb4xx_cpld {int /*<<< orphan*/  spi; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 unsigned char CPLD_CMD_WRITE_CFG ; 
 int /*<<< orphan*/  memset (struct spi_transfer**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spi_message_add_tail (struct spi_transfer*,struct spi_message*) ; 
 int /*<<< orphan*/  spi_message_init (struct spi_message*) ; 
 int spi_sync (int /*<<< orphan*/ ,struct spi_message*) ; 

__attribute__((used)) static int rb4xx_cpld_write_cfg(struct rb4xx_cpld *cpld, unsigned char config)
{
	struct spi_transfer t[1];
	struct spi_message m;
	unsigned char cmd[2];
	int err;

	spi_message_init(&m);
	memset(&t, 0, sizeof(t));

	t[0].tx_buf = cmd;
	t[0].len = sizeof(cmd);
	spi_message_add_tail(&t[0], &m);

	cmd[0] = CPLD_CMD_WRITE_CFG;
	cmd[1] = config;

	err = spi_sync(cpld->spi, &m);
	return err;
}