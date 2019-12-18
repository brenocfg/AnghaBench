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
struct mtd_info {int dummy; } ;
struct ar934x_nfc {int buf_index; int buf_size; int /*<<< orphan*/ * buf; scalar_t__ read_id; scalar_t__ swap_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct ar934x_nfc* mtd_to_ar934x_nfc (struct mtd_info*) ; 

__attribute__((used)) static u8
ar934x_nfc_read_byte(struct mtd_info *mtd)
{
	struct ar934x_nfc *nfc = mtd_to_ar934x_nfc(mtd);
	u8 data;

	WARN_ON(nfc->buf_index >= nfc->buf_size);

	if (nfc->swap_dma || nfc->read_id)
		data = nfc->buf[nfc->buf_index ^ 3];
	else
		data = nfc->buf[nfc->buf_index];

	nfc->buf_index++;

	return data;
}