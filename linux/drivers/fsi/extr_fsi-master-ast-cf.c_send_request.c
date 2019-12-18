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
typedef  unsigned int uint32_t ;
struct fsi_msg {int msg; unsigned int bits; } ;
struct fsi_master_acf {scalar_t__ sram; } ;

/* Variables and functions */
 unsigned int CMD_COMMAND ; 
 scalar_t__ CMD_DATA ; 
 unsigned int CMD_REG_CLEN_SHIFT ; 
 unsigned int CMD_REG_RLEN_SHIFT ; 
 int do_copro_command (struct fsi_master_acf*,unsigned int) ; 
 int /*<<< orphan*/  iowrite32be (int,scalar_t__) ; 
 int /*<<< orphan*/  trace_fsi_master_acf_send_request (struct fsi_master_acf*,struct fsi_msg*,unsigned int) ; 

__attribute__((used)) static int send_request(struct fsi_master_acf *master, struct fsi_msg *cmd,
			unsigned int resp_bits)
{
	uint32_t op;

	trace_fsi_master_acf_send_request(master, cmd, resp_bits);

	/* Store message into SRAM */
	iowrite32be((cmd->msg >> 32), master->sram + CMD_DATA);
	iowrite32be((cmd->msg & 0xffffffff), master->sram + CMD_DATA + 4);

	op = CMD_COMMAND;
	op |= cmd->bits << CMD_REG_CLEN_SHIFT;
	if (resp_bits)
		op |= resp_bits << CMD_REG_RLEN_SHIFT;

	return do_copro_command(master, op);
}