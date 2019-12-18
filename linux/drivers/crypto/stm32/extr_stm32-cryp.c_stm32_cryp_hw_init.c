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
struct stm32_cryp {int /*<<< orphan*/  flags; TYPE_3__* req; TYPE_2__* areq; int /*<<< orphan*/  dev; TYPE_1__* ctx; } ;
struct TYPE_6__ {scalar_t__ info; } ;
struct TYPE_5__ {int /*<<< orphan*/  assoclen; } ;
struct TYPE_4__ {int keylen; } ;

/* Variables and functions */
#define  AES_KEYSIZE_128 136 
#define  AES_KEYSIZE_192 135 
#define  AES_KEYSIZE_256 134 
 int /*<<< orphan*/  CRYP_CR ; 
 int /*<<< orphan*/  CRYP_IMSCR ; 
#define  CR_AES_CBC 133 
#define  CR_AES_CCM 132 
#define  CR_AES_CTR 131 
 int CR_AES_ECB ; 
#define  CR_AES_GCM 130 
 int CR_AES_KP ; 
 int CR_AES_UNKNOWN ; 
 int CR_CRYPEN ; 
 int CR_DATA8 ; 
 int CR_DEC_NOT_ENC ; 
#define  CR_DES_CBC 129 
 int CR_FFLUSH ; 
 int CR_KEY128 ; 
 int CR_KEY192 ; 
 int CR_KEY256 ; 
 int CR_PH_HEADER ; 
 int CR_PH_INIT ; 
 int CR_PH_PAYLOAD ; 
#define  CR_TDES_CBC 128 
 int EINVAL ; 
 int /*<<< orphan*/  FLG_CCM_PADDED_WA ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_decrypt (struct stm32_cryp*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int stm32_cryp_ccm_init (struct stm32_cryp*,int) ; 
 int stm32_cryp_gcm_init (struct stm32_cryp*,int) ; 
 int stm32_cryp_get_hw_mode (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_get_input_text_len (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_hw_write_iv (struct stm32_cryp*,int*) ; 
 int /*<<< orphan*/  stm32_cryp_hw_write_key (struct stm32_cryp*) ; 
 int stm32_cryp_wait_busy (struct stm32_cryp*) ; 
 int /*<<< orphan*/  stm32_cryp_write (struct stm32_cryp*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int stm32_cryp_hw_init(struct stm32_cryp *cryp)
{
	int ret;
	u32 cfg, hw_mode;

	pm_runtime_get_sync(cryp->dev);

	/* Disable interrupt */
	stm32_cryp_write(cryp, CRYP_IMSCR, 0);

	/* Set key */
	stm32_cryp_hw_write_key(cryp);

	/* Set configuration */
	cfg = CR_DATA8 | CR_FFLUSH;

	switch (cryp->ctx->keylen) {
	case AES_KEYSIZE_128:
		cfg |= CR_KEY128;
		break;

	case AES_KEYSIZE_192:
		cfg |= CR_KEY192;
		break;

	default:
	case AES_KEYSIZE_256:
		cfg |= CR_KEY256;
		break;
	}

	hw_mode = stm32_cryp_get_hw_mode(cryp);
	if (hw_mode == CR_AES_UNKNOWN)
		return -EINVAL;

	/* AES ECB/CBC decrypt: run key preparation first */
	if (is_decrypt(cryp) &&
	    ((hw_mode == CR_AES_ECB) || (hw_mode == CR_AES_CBC))) {
		stm32_cryp_write(cryp, CRYP_CR, cfg | CR_AES_KP | CR_CRYPEN);

		/* Wait for end of processing */
		ret = stm32_cryp_wait_busy(cryp);
		if (ret) {
			dev_err(cryp->dev, "Timeout (key preparation)\n");
			return ret;
		}
	}

	cfg |= hw_mode;

	if (is_decrypt(cryp))
		cfg |= CR_DEC_NOT_ENC;

	/* Apply config and flush (valid when CRYPEN = 0) */
	stm32_cryp_write(cryp, CRYP_CR, cfg);

	switch (hw_mode) {
	case CR_AES_GCM:
	case CR_AES_CCM:
		/* Phase 1 : init */
		if (hw_mode == CR_AES_CCM)
			ret = stm32_cryp_ccm_init(cryp, cfg);
		else
			ret = stm32_cryp_gcm_init(cryp, cfg);

		if (ret)
			return ret;

		/* Phase 2 : header (authenticated data) */
		if (cryp->areq->assoclen) {
			cfg |= CR_PH_HEADER;
		} else if (stm32_cryp_get_input_text_len(cryp)) {
			cfg |= CR_PH_PAYLOAD;
			stm32_cryp_write(cryp, CRYP_CR, cfg);
		} else {
			cfg |= CR_PH_INIT;
		}

		break;

	case CR_DES_CBC:
	case CR_TDES_CBC:
	case CR_AES_CBC:
	case CR_AES_CTR:
		stm32_cryp_hw_write_iv(cryp, (u32 *)cryp->req->info);
		break;

	default:
		break;
	}

	/* Enable now */
	cfg |= CR_CRYPEN;

	stm32_cryp_write(cryp, CRYP_CR, cfg);

	cryp->flags &= ~FLG_CCM_PADDED_WA;

	return 0;
}