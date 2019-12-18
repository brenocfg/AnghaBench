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
struct TYPE_4__ {int /*<<< orphan*/  has_dma; } ;
struct atmel_tdes_dev {int flags; TYPE_3__* req; TYPE_2__* ctx; TYPE_1__ caps; } ;
struct TYPE_6__ {scalar_t__ info; } ;
struct TYPE_5__ {int keylen; scalar_t__ key; } ;

/* Variables and functions */
 int DES_KEY_SIZE ; 
 int /*<<< orphan*/  TDES_CR ; 
 int TDES_FLAGS_CBC ; 
 int TDES_FLAGS_CFB ; 
 int TDES_FLAGS_CFB16 ; 
 int TDES_FLAGS_CFB32 ; 
 int TDES_FLAGS_CFB64 ; 
 int TDES_FLAGS_CFB8 ; 
 int TDES_FLAGS_ENCRYPT ; 
 int TDES_FLAGS_OFB ; 
 int /*<<< orphan*/  TDES_IV1R ; 
 int /*<<< orphan*/  TDES_KEY1W1R ; 
 int /*<<< orphan*/  TDES_MR ; 
 int TDES_MR_CFBS_16b ; 
 int TDES_MR_CFBS_32b ; 
 int TDES_MR_CFBS_64b ; 
 int TDES_MR_CFBS_8b ; 
 int TDES_MR_CYPHER_ENC ; 
 int TDES_MR_KEYMOD_2KEY ; 
 int TDES_MR_KEYMOD_3KEY ; 
 int TDES_MR_OPMOD_CBC ; 
 int TDES_MR_OPMOD_CFB ; 
 int TDES_MR_OPMOD_OFB ; 
 int TDES_MR_SMOD_PDC ; 
 int TDES_MR_TDESMOD_DES ; 
 int TDES_MR_TDESMOD_TDES ; 
 int /*<<< orphan*/  TDES_PTCR ; 
 int TDES_PTCR_RXTDIS ; 
 int TDES_PTCR_TXTDIS ; 
 int atmel_tdes_hw_init (struct atmel_tdes_dev*) ; 
 int /*<<< orphan*/  atmel_tdes_write (struct atmel_tdes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atmel_tdes_write_n (struct atmel_tdes_dev*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static int atmel_tdes_write_ctrl(struct atmel_tdes_dev *dd)
{
	int err;
	u32 valcr = 0, valmr = TDES_MR_SMOD_PDC;

	err = atmel_tdes_hw_init(dd);

	if (err)
		return err;

	if (!dd->caps.has_dma)
		atmel_tdes_write(dd, TDES_PTCR,
			TDES_PTCR_TXTDIS | TDES_PTCR_RXTDIS);

	/* MR register must be set before IV registers */
	if (dd->ctx->keylen > (DES_KEY_SIZE << 1)) {
		valmr |= TDES_MR_KEYMOD_3KEY;
		valmr |= TDES_MR_TDESMOD_TDES;
	} else if (dd->ctx->keylen > DES_KEY_SIZE) {
		valmr |= TDES_MR_KEYMOD_2KEY;
		valmr |= TDES_MR_TDESMOD_TDES;
	} else {
		valmr |= TDES_MR_TDESMOD_DES;
	}

	if (dd->flags & TDES_FLAGS_CBC) {
		valmr |= TDES_MR_OPMOD_CBC;
	} else if (dd->flags & TDES_FLAGS_CFB) {
		valmr |= TDES_MR_OPMOD_CFB;

		if (dd->flags & TDES_FLAGS_CFB8)
			valmr |= TDES_MR_CFBS_8b;
		else if (dd->flags & TDES_FLAGS_CFB16)
			valmr |= TDES_MR_CFBS_16b;
		else if (dd->flags & TDES_FLAGS_CFB32)
			valmr |= TDES_MR_CFBS_32b;
		else if (dd->flags & TDES_FLAGS_CFB64)
			valmr |= TDES_MR_CFBS_64b;
	} else if (dd->flags & TDES_FLAGS_OFB) {
		valmr |= TDES_MR_OPMOD_OFB;
	}

	if ((dd->flags & TDES_FLAGS_ENCRYPT) || (dd->flags & TDES_FLAGS_OFB))
		valmr |= TDES_MR_CYPHER_ENC;

	atmel_tdes_write(dd, TDES_CR, valcr);
	atmel_tdes_write(dd, TDES_MR, valmr);

	atmel_tdes_write_n(dd, TDES_KEY1W1R, dd->ctx->key,
						dd->ctx->keylen >> 2);

	if (((dd->flags & TDES_FLAGS_CBC) || (dd->flags & TDES_FLAGS_CFB) ||
		(dd->flags & TDES_FLAGS_OFB)) && dd->req->info) {
		atmel_tdes_write_n(dd, TDES_IV1R, dd->req->info, 2);
	}

	return 0;
}