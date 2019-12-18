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
struct scatterlist {int dummy; } ;
struct atmel_i2c_cmd {int /*<<< orphan*/  rxsize; int /*<<< orphan*/  msecs; int /*<<< orphan*/  data; int /*<<< orphan*/  param2; int /*<<< orphan*/  param1; int /*<<< orphan*/  opcode; int /*<<< orphan*/  count; int /*<<< orphan*/  word_addr; } ;

/* Variables and functions */
 size_t ATMEL_ECC_PUBKEY_SIZE ; 
 int /*<<< orphan*/  COMMAND ; 
 int /*<<< orphan*/  DATA_SLOT_2 ; 
 int /*<<< orphan*/  ECDH_COUNT ; 
 int /*<<< orphan*/  ECDH_PREFIX_MODE ; 
 int /*<<< orphan*/  ECDH_RSP_SIZE ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX_EXEC_TIME_ECDH ; 
 int /*<<< orphan*/  OPCODE_ECDH ; 
 int /*<<< orphan*/  atmel_i2c_checksum (struct atmel_i2c_cmd*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 size_t sg_copy_to_buffer (struct scatterlist*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sg_nents_for_len (struct scatterlist*,size_t) ; 

int atmel_i2c_init_ecdh_cmd(struct atmel_i2c_cmd *cmd,
			    struct scatterlist *pubkey)
{
	size_t copied;

	cmd->word_addr = COMMAND;
	cmd->count = ECDH_COUNT;
	cmd->opcode = OPCODE_ECDH;
	cmd->param1 = ECDH_PREFIX_MODE;
	/* private key slot */
	cmd->param2 = cpu_to_le16(DATA_SLOT_2);

	/*
	 * The device only supports NIST P256 ECC keys. The public key size will
	 * always be the same. Use a macro for the key size to avoid unnecessary
	 * computations.
	 */
	copied = sg_copy_to_buffer(pubkey,
				   sg_nents_for_len(pubkey,
						    ATMEL_ECC_PUBKEY_SIZE),
				   cmd->data, ATMEL_ECC_PUBKEY_SIZE);
	if (copied != ATMEL_ECC_PUBKEY_SIZE)
		return -EINVAL;

	atmel_i2c_checksum(cmd);

	cmd->msecs = MAX_EXEC_TIME_ECDH;
	cmd->rxsize = ECDH_RSP_SIZE;

	return 0;
}