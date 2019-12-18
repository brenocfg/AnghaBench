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
struct TYPE_2__ {int /*<<< orphan*/  mode; } ;
struct nand_chip {TYPE_1__ ecc; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct ar934x_nfc {int read_id; int buf_index; int rndout_page_addr; unsigned int rndout_read_cmd; int erase1_page_addr; int seqin_read_cmd; int seqin_column; int seqin_page_addr; int /*<<< orphan*/  parent; int /*<<< orphan*/  small_page; struct nand_chip nand_chip; } ;

/* Variables and functions */
#define  NAND_CMD_ERASE1 138 
#define  NAND_CMD_ERASE2 137 
#define  NAND_CMD_PAGEPROG 136 
#define  NAND_CMD_READ0 135 
#define  NAND_CMD_READ1 134 
#define  NAND_CMD_READID 133 
#define  NAND_CMD_READOOB 132 
#define  NAND_CMD_RESET 131 
#define  NAND_CMD_RNDOUT 130 
#define  NAND_CMD_SEQIN 129 
#define  NAND_CMD_STATUS 128 
 int /*<<< orphan*/  NAND_ECC_HW ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar934x_nfc_read_status (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_send_cmd (struct ar934x_nfc*,unsigned int) ; 
 int /*<<< orphan*/  ar934x_nfc_send_erase (struct ar934x_nfc*,unsigned int,int,int) ; 
 int /*<<< orphan*/  ar934x_nfc_send_read (struct ar934x_nfc*,int const,int,int,int) ; 
 int /*<<< orphan*/  ar934x_nfc_send_readid (struct ar934x_nfc*,unsigned int) ; 
 int /*<<< orphan*/  ar934x_nfc_send_write (struct ar934x_nfc*,unsigned int,int,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int,int,int) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 

__attribute__((used)) static void
ar934x_nfc_cmdfunc(struct mtd_info *mtd, unsigned int command, int column,
		   int page_addr)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	struct nand_chip *nand = &nfc->nand_chip;

	nfc->read_id = false;
	if (command != NAND_CMD_PAGEPROG)
		nfc->buf_index = 0;

	switch (command) {
	case NAND_CMD_RESET:
		ar934x_nfc_send_cmd(nfc, command);
		break;

	case NAND_CMD_READID:
		nfc->read_id = true;
		ar934x_nfc_send_readid(nfc, command);
		break;

	case NAND_CMD_READ0:
	case NAND_CMD_READ1:
		if (nfc->small_page) {
			ar934x_nfc_send_read(nfc, command, column, page_addr,
					     mtd->writesize + mtd->oobsize);
		} else {
			ar934x_nfc_send_read(nfc, command, 0, page_addr,
					     mtd->writesize + mtd->oobsize);
			nfc->buf_index = column;
			nfc->rndout_page_addr = page_addr;
			nfc->rndout_read_cmd = command;
		}
		break;

	case NAND_CMD_READOOB:
		if (nfc->small_page)
			ar934x_nfc_send_read(nfc, NAND_CMD_READOOB,
					     column, page_addr,
					     mtd->oobsize);
		else
			ar934x_nfc_send_read(nfc, NAND_CMD_READ0,
					     mtd->writesize, page_addr,
					     mtd->oobsize);
		break;

	case NAND_CMD_RNDOUT:
		if (WARN_ON(nfc->small_page))
			break;

		/* emulate subpage read */
		ar934x_nfc_send_read(nfc, nfc->rndout_read_cmd, 0,
				     nfc->rndout_page_addr,
				     mtd->writesize + mtd->oobsize);
		nfc->buf_index = column;
		break;

	case NAND_CMD_ERASE1:
		nfc->erase1_page_addr = page_addr;
		break;

	case NAND_CMD_ERASE2:
		ar934x_nfc_send_erase(nfc, command, -1, nfc->erase1_page_addr);
		break;

	case NAND_CMD_STATUS:
		ar934x_nfc_read_status(nfc);
		break;

	case NAND_CMD_SEQIN:
		if (nfc->small_page) {
			/* output read command */
			if (column >= mtd->writesize) {
				column -= mtd->writesize;
				nfc->seqin_read_cmd = NAND_CMD_READOOB;
			} else if (column < 256) {
				nfc->seqin_read_cmd = NAND_CMD_READ0;
			} else {
				column -= 256;
				nfc->seqin_read_cmd = NAND_CMD_READ1;
			}
		} else {
			nfc->seqin_read_cmd = NAND_CMD_READ0;
		}
		nfc->seqin_column = column;
		nfc->seqin_page_addr = page_addr;
		break;

	case NAND_CMD_PAGEPROG:
		if (nand->ecc.mode == NAND_ECC_HW) {
			/* the data is already written */
			break;
		}

		if (nfc->small_page)
			ar934x_nfc_send_cmd(nfc, nfc->seqin_read_cmd);

		ar934x_nfc_send_write(nfc, command, nfc->seqin_column,
				      nfc->seqin_page_addr,
				      nfc->buf_index);
		break;

	default:
		dev_err(nfc->parent,
			"unsupported command: %x, column:%d page_addr=%d\n",
			command, column, page_addr);
		break;
	}
}