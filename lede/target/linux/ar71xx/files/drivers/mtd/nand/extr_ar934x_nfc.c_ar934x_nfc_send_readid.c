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
typedef  unsigned int u32 ;
struct ar934x_nfc {int /*<<< orphan*/  buf; int /*<<< orphan*/  ctrl_reg; } ;

/* Variables and functions */
 unsigned int AR934X_NFC_CMD_CMD0_M ; 
 unsigned int AR934X_NFC_CMD_CMD0_S ; 
 unsigned int AR934X_NFC_CMD_SEQ_1C1AXR ; 
 int /*<<< orphan*/  AR934X_NFC_ID_BUF_SIZE ; 
 int ar934x_nfc_do_rw_command (struct ar934x_nfc*,int,int,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,unsigned int) ; 
 int /*<<< orphan*/  nfc_debug_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ar934x_nfc_send_readid(struct ar934x_nfc *nfc, unsigned command)
{
	u32 cmd_reg;
	int err;

	nfc_dbg(nfc, "readid, cmd:%02x\n", command);

	cmd_reg = AR934X_NFC_CMD_SEQ_1C1AXR;
	cmd_reg |= (command & AR934X_NFC_CMD_CMD0_M) << AR934X_NFC_CMD_CMD0_S;

	err = ar934x_nfc_do_rw_command(nfc, -1, -1, AR934X_NFC_ID_BUF_SIZE,
				       cmd_reg, nfc->ctrl_reg, false);

	nfc_debug_data("[id] ", nfc->buf, AR934X_NFC_ID_BUF_SIZE);

	return err;
}