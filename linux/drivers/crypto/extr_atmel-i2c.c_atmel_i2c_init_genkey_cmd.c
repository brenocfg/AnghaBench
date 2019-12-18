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
typedef  int /*<<< orphan*/  u16 ;
struct atmel_i2c_cmd {int /*<<< orphan*/  rxsize; int /*<<< orphan*/  msecs; int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  opcode; int /*<<< orphan*/  count; int /*<<< orphan*/  word_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  GENKEY_COUNT ; 
 int /*<<< orphan*/  GENKEY_MODE_PRIVATE ; 
 int /*<<< orphan*/  GENKEY_RSP_SIZE ; 
 int /*<<< orphan*/  MAX_EXEC_TIME_GENKEY ; 
 int /*<<< orphan*/  OPCODE_GENKEY ; 
 int /*<<< orphan*/  atmel_i2c_checksum (struct atmel_i2c_cmd*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 

void atmel_i2c_init_genkey_cmd(struct atmel_i2c_cmd *cmd, u16 keyid)
{
	cmd->word_addr = COMMAND;
	cmd->count = GENKEY_COUNT;
	cmd->opcode = OPCODE_GENKEY;
	cmd->param1 = GENKEY_MODE_PRIVATE;
	/* a random private key will be generated and stored in slot keyID */
	cmd->param2 = cpu_to_le16(keyid);

	atmel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_GENKEY;
	cmd->rxsize = GENKEY_RSP_SIZE;
}