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
struct ar934x_nfc {int /*<<< orphan*/  ctrl_reg; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 unsigned int AR934X_NFC_CMD_CMD0_S ; 
 unsigned int AR934X_NFC_CMD_CMD1_S ; 
 unsigned int AR934X_NFC_CMD_SEQ_12 ; 
 unsigned int NAND_CMD_SEQIN ; 
 int ar934x_nfc_do_rw_command (struct ar934x_nfc*,int,int,int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int,int) ; 
 int /*<<< orphan*/  nfc_debug_data (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ar934x_nfc_send_write(struct ar934x_nfc *nfc, unsigned command, int column,
		     int page_addr, int len)
{
	u32 cmd_reg;

	nfc_dbg(nfc, "write, column=%d page=%d len=%d\n",
		column, page_addr, len);

	nfc_debug_data("[data] ", nfc->buf, len);

	cmd_reg = NAND_CMD_SEQIN << AR934X_NFC_CMD_CMD0_S;
	cmd_reg |= command << AR934X_NFC_CMD_CMD1_S;
	cmd_reg |= AR934X_NFC_CMD_SEQ_12;

	return ar934x_nfc_do_rw_command(nfc, column, page_addr, len,
					cmd_reg, nfc->ctrl_reg, true);
}