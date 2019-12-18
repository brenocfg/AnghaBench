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
typedef  int u32 ;
struct nand_chip {int chipsize; } ;
struct mtd_info {int oobsize; int erasesize; int writesize; } ;
struct ar934x_nfc {int small_page; int addr_count0; int addr_count1; int ctrl_reg; int /*<<< orphan*/  parent; struct nand_chip nand_chip; } ;

/* Variables and functions */
 int AR934X_NFC_CTRL_ADDR_CYCLE0_S ; 
 int AR934X_NFC_CTRL_ADDR_CYCLE1_S ; 
 int AR934X_NFC_CTRL_BLOCK_SIZE_128 ; 
 int AR934X_NFC_CTRL_BLOCK_SIZE_256 ; 
 int AR934X_NFC_CTRL_BLOCK_SIZE_32 ; 
 int AR934X_NFC_CTRL_BLOCK_SIZE_64 ; 
 int AR934X_NFC_CTRL_BLOCK_SIZE_S ; 
 int AR934X_NFC_CTRL_CUSTOM_SIZE_EN ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_1024 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_16384 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_2048 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_256 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_4096 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_512 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_8192 ; 
 int AR934X_NFC_CTRL_PAGE_SIZE_S ; 
 int AR934X_NFC_CTRL_SMALL_PAGE ; 
 int /*<<< orphan*/  AR934X_NFC_REG_CTRL ; 
 int /*<<< orphan*/  AR934X_NFC_REG_SPARE_SIZE ; 
 int ENXIO ; 
 int ar934x_nfc_alloc_buf (struct ar934x_nfc*,int) ; 
 int /*<<< orphan*/  ar934x_nfc_free_buf (struct ar934x_nfc*) ; 
 int /*<<< orphan*/  ar934x_nfc_wr (struct ar934x_nfc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 

__attribute__((used)) static int
ar934x_nfc_init_tail(struct mtd_info *mtd)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	struct nand_chip *chip = &nfc->nand_chip;
	u32 ctrl;
	u32 t;
	int err;

	switch (mtd->oobsize) {
	case 16:
	case 64:
	case 128:
		ar934x_nfc_wr(nfc, AR934X_NFC_REG_SPARE_SIZE, mtd->oobsize);
		break;

	default:
		dev_err(nfc->parent, "unsupported OOB size: %d bytes\n",
			mtd->oobsize);
		return -ENXIO;
	}

	ctrl = AR934X_NFC_CTRL_CUSTOM_SIZE_EN;

	switch (mtd->erasesize / mtd->writesize) {
	case 32:
		t = AR934X_NFC_CTRL_BLOCK_SIZE_32;
		break;

	case 64:
		t = AR934X_NFC_CTRL_BLOCK_SIZE_64;
		break;

	case 128:
		t = AR934X_NFC_CTRL_BLOCK_SIZE_128;
		break;

	case 256:
		t = AR934X_NFC_CTRL_BLOCK_SIZE_256;
		break;

	default:
		dev_err(nfc->parent, "unsupported block size: %u\n",
			mtd->erasesize / mtd->writesize);
		return -ENXIO;
	}

	ctrl |= t << AR934X_NFC_CTRL_BLOCK_SIZE_S;

	switch (mtd->writesize) {
	case 256:
		nfc->small_page = 1;
		t = AR934X_NFC_CTRL_PAGE_SIZE_256;
		break;

	case 512:
		nfc->small_page = 1;
		t = AR934X_NFC_CTRL_PAGE_SIZE_512;
		break;

	case 1024:
		t = AR934X_NFC_CTRL_PAGE_SIZE_1024;
		break;

	case 2048:
		t = AR934X_NFC_CTRL_PAGE_SIZE_2048;
		break;

	case 4096:
		t = AR934X_NFC_CTRL_PAGE_SIZE_4096;
		break;

	case 8192:
		t = AR934X_NFC_CTRL_PAGE_SIZE_8192;
		break;

	case 16384:
		t = AR934X_NFC_CTRL_PAGE_SIZE_16384;
		break;

	default:
		dev_err(nfc->parent, "unsupported write size: %d bytes\n",
			mtd->writesize);
		return -ENXIO;
	}

	ctrl |= t << AR934X_NFC_CTRL_PAGE_SIZE_S;

	if (nfc->small_page) {
		ctrl |= AR934X_NFC_CTRL_SMALL_PAGE;

		if (chip->chipsize > (32 << 20)) {
			nfc->addr_count0 = 4;
			nfc->addr_count1 = 3;
		} else if (chip->chipsize > (2 << 16)) {
			nfc->addr_count0 = 3;
			nfc->addr_count1 = 2;
		} else {
			nfc->addr_count0 = 2;
			nfc->addr_count1 = 1;
		}
	} else {
		if (chip->chipsize > (128 << 20)) {
			nfc->addr_count0 = 5;
			nfc->addr_count1 = 3;
		} else if (chip->chipsize > (8 << 16)) {
			nfc->addr_count0 = 4;
			nfc->addr_count1 = 2;
		} else {
			nfc->addr_count0 = 3;
			nfc->addr_count1 = 1;
		}
	}

	ctrl |= nfc->addr_count0 << AR934X_NFC_CTRL_ADDR_CYCLE0_S;
	ctrl |= nfc->addr_count1 << AR934X_NFC_CTRL_ADDR_CYCLE1_S;

	nfc->ctrl_reg = ctrl;
	ar934x_nfc_wr(nfc, AR934X_NFC_REG_CTRL, nfc->ctrl_reg);

	ar934x_nfc_free_buf(nfc);
	err = ar934x_nfc_alloc_buf(nfc, mtd->writesize + mtd->oobsize);

	return err;
}