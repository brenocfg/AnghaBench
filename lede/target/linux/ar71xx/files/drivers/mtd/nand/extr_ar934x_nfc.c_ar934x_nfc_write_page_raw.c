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
typedef  int /*<<< orphan*/  u8 ;
struct nand_chip {int /*<<< orphan*/  const* oob_poi; } ;
struct mtd_info {int writesize; int oobsize; } ;
struct ar934x_nfc {int /*<<< orphan*/ * buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  NAND_CMD_PAGEPROG ; 
 int ar934x_nfc_send_write (struct ar934x_nfc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 
 int /*<<< orphan*/  nfc_dbg (struct ar934x_nfc*,char*,int,int) ; 

__attribute__((used)) static int
ar934x_nfc_write_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
			  const u8 *buf, int oob_required, int page)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	int len;

	nfc_dbg(nfc, "write_page_raw: page:%d oob:%d\n", page, oob_required);

	memcpy(nfc->buf, buf, mtd->writesize);
	len = mtd->writesize;

	if (oob_required) {
		memcpy(&nfc->buf[mtd->writesize], chip->oob_poi, mtd->oobsize);
		len += mtd->oobsize;
	}

	return ar934x_nfc_send_write(nfc, NAND_CMD_PAGEPROG, 0, page, len);
}