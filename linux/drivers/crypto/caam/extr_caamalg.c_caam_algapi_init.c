#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_17__ {TYPE_5__ base; } ;
struct TYPE_13__ {int class1_alg_type; } ;
struct caam_skcipher_alg {int registered; TYPE_8__ skcipher; TYPE_4__ caam; } ;
struct caam_drv_private {int era; TYPE_3__* ctrl; } ;
struct TYPE_16__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_18__ {unsigned int maxauthsize; TYPE_7__ base; } ;
struct TYPE_15__ {int class1_alg_type; int class2_alg_type; } ;
struct caam_aead_alg {int registered; TYPE_9__ aead; TYPE_6__ caam; } ;
struct TYPE_11__ {int /*<<< orphan*/  afha; int /*<<< orphan*/  ptha; int /*<<< orphan*/  ccha; int /*<<< orphan*/  desa; int /*<<< orphan*/  mdha; int /*<<< orphan*/  aesa; } ;
struct TYPE_10__ {int /*<<< orphan*/  cha_rev_ls; int /*<<< orphan*/  cha_num_ls; int /*<<< orphan*/  cha_id_ls; } ;
struct TYPE_12__ {TYPE_2__ vreg; TYPE_1__ perfmon; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int CHA_ID_LS_AES_MASK ; 
 int CHA_ID_LS_ARC4_MASK ; 
 int CHA_ID_LS_ARC4_SHIFT ; 
 int CHA_ID_LS_DES_MASK ; 
 int CHA_ID_LS_DES_SHIFT ; 
 int CHA_ID_LS_MD_MASK ; 
 int CHA_ID_LS_MD_SHIFT ; 
 int CHA_VER_MISC_AES_GCM ; 
 int CHA_VER_NUM_MASK ; 
 int CHA_VER_VID_AES_LP ; 
 int CHA_VER_VID_MASK ; 
 int CHA_VER_VID_MD_LP256 ; 
 int CHA_VER_VID_SHIFT ; 
 int OP_ALG_AAI_GCM ; 
 int OP_ALG_AAI_MASK ; 
 int OP_ALG_AAI_XTS ; 
 int OP_ALG_ALGSEL_3DES ; 
 int OP_ALG_ALGSEL_AES ; 
 int OP_ALG_ALGSEL_ARC4 ; 
 int OP_ALG_ALGSEL_CHACHA20 ; 
 int OP_ALG_ALGSEL_DES ; 
 int OP_ALG_ALGSEL_MASK ; 
 int OP_ALG_ALGSEL_POLY1305 ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 unsigned int SHA512_DIGEST_SIZE ; 
 int /*<<< orphan*/  caam_aead_alg_init (struct caam_aead_alg*) ; 
 int /*<<< orphan*/  caam_skcipher_alg_init (struct caam_skcipher_alg*) ; 
 int crypto_register_aead (TYPE_9__*) ; 
 int crypto_register_skcipher (TYPE_8__*) ; 
 struct caam_drv_private* dev_get_drvdata (struct device*) ; 
 void* driver_aeads ; 
 void* driver_algs ; 
 scalar_t__ is_mdha (int) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int rd_reg32 (int /*<<< orphan*/ *) ; 

int caam_algapi_init(struct device *ctrldev)
{
	struct caam_drv_private *priv = dev_get_drvdata(ctrldev);
	int i = 0, err = 0;
	u32 aes_vid, aes_inst, des_inst, md_vid, md_inst, ccha_inst, ptha_inst;
	u32 arc4_inst;
	unsigned int md_limit = SHA512_DIGEST_SIZE;
	bool registered = false, gcm_support;

	/*
	 * Register crypto algorithms the device supports.
	 * First, detect presence and attributes of DES, AES, and MD blocks.
	 */
	if (priv->era < 10) {
		u32 cha_vid, cha_inst, aes_rn;

		cha_vid = rd_reg32(&priv->ctrl->perfmon.cha_id_ls);
		aes_vid = cha_vid & CHA_ID_LS_AES_MASK;
		md_vid = (cha_vid & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;

		cha_inst = rd_reg32(&priv->ctrl->perfmon.cha_num_ls);
		des_inst = (cha_inst & CHA_ID_LS_DES_MASK) >>
			   CHA_ID_LS_DES_SHIFT;
		aes_inst = cha_inst & CHA_ID_LS_AES_MASK;
		md_inst = (cha_inst & CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
		arc4_inst = (cha_inst & CHA_ID_LS_ARC4_MASK) >>
			    CHA_ID_LS_ARC4_SHIFT;
		ccha_inst = 0;
		ptha_inst = 0;

		aes_rn = rd_reg32(&priv->ctrl->perfmon.cha_rev_ls) &
			 CHA_ID_LS_AES_MASK;
		gcm_support = !(aes_vid == CHA_VER_VID_AES_LP && aes_rn < 8);
	} else {
		u32 aesa, mdha;

		aesa = rd_reg32(&priv->ctrl->vreg.aesa);
		mdha = rd_reg32(&priv->ctrl->vreg.mdha);

		aes_vid = (aesa & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;
		md_vid = (mdha & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;

		des_inst = rd_reg32(&priv->ctrl->vreg.desa) & CHA_VER_NUM_MASK;
		aes_inst = aesa & CHA_VER_NUM_MASK;
		md_inst = mdha & CHA_VER_NUM_MASK;
		ccha_inst = rd_reg32(&priv->ctrl->vreg.ccha) & CHA_VER_NUM_MASK;
		ptha_inst = rd_reg32(&priv->ctrl->vreg.ptha) & CHA_VER_NUM_MASK;
		arc4_inst = rd_reg32(&priv->ctrl->vreg.afha) & CHA_VER_NUM_MASK;

		gcm_support = aesa & CHA_VER_MISC_AES_GCM;
	}

	/* If MD is present, limit digest size based on LP256 */
	if (md_inst && md_vid  == CHA_VER_VID_MD_LP256)
		md_limit = SHA256_DIGEST_SIZE;

	for (i = 0; i < ARRAY_SIZE(driver_algs); i++) {
		struct caam_skcipher_alg *t_alg = driver_algs + i;
		u32 alg_sel = t_alg->caam.class1_alg_type & OP_ALG_ALGSEL_MASK;

		/* Skip DES algorithms if not supported by device */
		if (!des_inst &&
		    ((alg_sel == OP_ALG_ALGSEL_3DES) ||
		     (alg_sel == OP_ALG_ALGSEL_DES)))
				continue;

		/* Skip AES algorithms if not supported by device */
		if (!aes_inst && (alg_sel == OP_ALG_ALGSEL_AES))
				continue;

		/* Skip ARC4 algorithms if not supported by device */
		if (!arc4_inst && alg_sel == OP_ALG_ALGSEL_ARC4)
			continue;

		/*
		 * Check support for AES modes not available
		 * on LP devices.
		 */
		if (aes_vid == CHA_VER_VID_AES_LP &&
		    (t_alg->caam.class1_alg_type & OP_ALG_AAI_MASK) ==
		    OP_ALG_AAI_XTS)
			continue;

		caam_skcipher_alg_init(t_alg);

		err = crypto_register_skcipher(&t_alg->skcipher);
		if (err) {
			pr_warn("%s alg registration failed\n",
				t_alg->skcipher.base.cra_driver_name);
			continue;
		}

		t_alg->registered = true;
		registered = true;
	}

	for (i = 0; i < ARRAY_SIZE(driver_aeads); i++) {
		struct caam_aead_alg *t_alg = driver_aeads + i;
		u32 c1_alg_sel = t_alg->caam.class1_alg_type &
				 OP_ALG_ALGSEL_MASK;
		u32 c2_alg_sel = t_alg->caam.class2_alg_type &
				 OP_ALG_ALGSEL_MASK;
		u32 alg_aai = t_alg->caam.class1_alg_type & OP_ALG_AAI_MASK;

		/* Skip DES algorithms if not supported by device */
		if (!des_inst &&
		    ((c1_alg_sel == OP_ALG_ALGSEL_3DES) ||
		     (c1_alg_sel == OP_ALG_ALGSEL_DES)))
				continue;

		/* Skip AES algorithms if not supported by device */
		if (!aes_inst && (c1_alg_sel == OP_ALG_ALGSEL_AES))
				continue;

		/* Skip CHACHA20 algorithms if not supported by device */
		if (c1_alg_sel == OP_ALG_ALGSEL_CHACHA20 && !ccha_inst)
			continue;

		/* Skip POLY1305 algorithms if not supported by device */
		if (c2_alg_sel == OP_ALG_ALGSEL_POLY1305 && !ptha_inst)
			continue;

		/* Skip GCM algorithms if not supported by device */
		if (c1_alg_sel == OP_ALG_ALGSEL_AES &&
		    alg_aai == OP_ALG_AAI_GCM && !gcm_support)
			continue;

		/*
		 * Skip algorithms requiring message digests
		 * if MD or MD size is not supported by device.
		 */
		if (is_mdha(c2_alg_sel) &&
		    (!md_inst || t_alg->aead.maxauthsize > md_limit))
			continue;

		caam_aead_alg_init(t_alg);

		err = crypto_register_aead(&t_alg->aead);
		if (err) {
			pr_warn("%s alg registration failed\n",
				t_alg->aead.base.cra_driver_name);
			continue;
		}

		t_alg->registered = true;
		registered = true;
	}

	if (registered)
		pr_info("caam algorithms registered in /proc/crypto\n");

	return err;
}