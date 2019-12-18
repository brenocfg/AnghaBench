#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {void* length; } ;
struct TYPE_5__ {void* length; void* hsn; void* tsn; } ;
struct TYPE_4__ {void* length; } ;
struct opal_header {TYPE_3__ cp; TYPE_2__ pkt; TYPE_1__ subpkt; } ;
struct opal_dev {int pos; scalar_t__* cmd; } ;

/* Variables and functions */
 int EFAULT ; 
 int ERANGE ; 
 int IO_BUFFER_LENGTH ; 
 int /*<<< orphan*/  OPAL_ENDLIST ; 
 int /*<<< orphan*/  OPAL_ENDOFDATA ; 
 int /*<<< orphan*/  OPAL_STARTLIST ; 
 int /*<<< orphan*/  add_token_u8 (int*,struct opal_dev*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int cmd_finalize(struct opal_dev *cmd, u32 hsn, u32 tsn)
{
	struct opal_header *hdr;
	int err = 0;

	/*
	 * Close the parameter list opened from cmd_start.
	 * The number of bytes added must be equal to
	 * CMD_FINALIZE_BYTES_NEEDED.
	 */
	add_token_u8(&err, cmd, OPAL_ENDLIST);

	add_token_u8(&err, cmd, OPAL_ENDOFDATA);
	add_token_u8(&err, cmd, OPAL_STARTLIST);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, 0);
	add_token_u8(&err, cmd, OPAL_ENDLIST);

	if (err) {
		pr_debug("Error finalizing command.\n");
		return -EFAULT;
	}

	hdr = (struct opal_header *) cmd->cmd;

	hdr->pkt.tsn = cpu_to_be32(tsn);
	hdr->pkt.hsn = cpu_to_be32(hsn);

	hdr->subpkt.length = cpu_to_be32(cmd->pos - sizeof(*hdr));
	while (cmd->pos % 4) {
		if (cmd->pos >= IO_BUFFER_LENGTH) {
			pr_debug("Error: Buffer overrun\n");
			return -ERANGE;
		}
		cmd->cmd[cmd->pos++] = 0;
	}
	hdr->pkt.length = cpu_to_be32(cmd->pos - sizeof(hdr->cp) -
				      sizeof(hdr->pkt));
	hdr->cp.length = cpu_to_be32(cmd->pos - sizeof(hdr->cp));

	return 0;
}