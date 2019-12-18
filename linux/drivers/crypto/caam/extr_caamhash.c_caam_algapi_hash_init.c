#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct TYPE_12__ {unsigned int digestsize; } ;
struct TYPE_13__ {TYPE_4__ halg; } ;
struct caam_hash_template {int alg_type; int /*<<< orphan*/  driver_name; int /*<<< orphan*/  hmac_driver_name; TYPE_5__ template_ahash; } ;
struct TYPE_14__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_15__ {TYPE_6__ base; } ;
struct TYPE_16__ {TYPE_7__ halg; } ;
struct caam_hash_alg {int /*<<< orphan*/  entry; TYPE_8__ ahash_alg; } ;
struct caam_drv_private {int era; TYPE_3__* ctrl; } ;
struct TYPE_10__ {int /*<<< orphan*/  mdha; } ;
struct TYPE_9__ {int /*<<< orphan*/  cha_num_ls; int /*<<< orphan*/  cha_id_ls; } ;
struct TYPE_11__ {TYPE_2__ vreg; TYPE_1__ perfmon; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct caam_hash_template*) ; 
 int CHA_ID_LS_MD_MASK ; 
 int CHA_ID_LS_MD_SHIFT ; 
 int CHA_VER_NUM_MASK ; 
 int CHA_VER_VID_MASK ; 
 int CHA_VER_VID_MD_LP256 ; 
 int CHA_VER_VID_SHIFT ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct caam_hash_alg*) ; 
 int OP_ALG_ALGSEL_AES ; 
 int OP_ALG_ALGSEL_MASK ; 
 int PTR_ERR (struct caam_hash_alg*) ; 
 unsigned int SHA256_DIGEST_SIZE ; 
 unsigned int SHA512_DIGEST_SIZE ; 
 struct caam_hash_alg* caam_hash_alloc (struct caam_hash_template*,int) ; 
 int crypto_register_ahash (TYPE_8__*) ; 
 struct caam_drv_private* dev_get_drvdata (struct device*) ; 
 struct caam_hash_template* driver_hash ; 
 int /*<<< orphan*/  hash_list ; 
 scalar_t__ is_mdha (int) ; 
 int /*<<< orphan*/  kfree (struct caam_hash_alg*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,...) ; 
 int rd_reg32 (int /*<<< orphan*/ *) ; 

int caam_algapi_hash_init(struct device *ctrldev)
{
	int i = 0, err = 0;
	struct caam_drv_private *priv = dev_get_drvdata(ctrldev);
	unsigned int md_limit = SHA512_DIGEST_SIZE;
	u32 md_inst, md_vid;

	/*
	 * Register crypto algorithms the device supports.  First, identify
	 * presence and attributes of MD block.
	 */
	if (priv->era < 10) {
		md_vid = (rd_reg32(&priv->ctrl->perfmon.cha_id_ls) &
			  CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
		md_inst = (rd_reg32(&priv->ctrl->perfmon.cha_num_ls) &
			   CHA_ID_LS_MD_MASK) >> CHA_ID_LS_MD_SHIFT;
	} else {
		u32 mdha = rd_reg32(&priv->ctrl->vreg.mdha);

		md_vid = (mdha & CHA_VER_VID_MASK) >> CHA_VER_VID_SHIFT;
		md_inst = mdha & CHA_VER_NUM_MASK;
	}

	/*
	 * Skip registration of any hashing algorithms if MD block
	 * is not present.
	 */
	if (!md_inst)
		return 0;

	/* Limit digest size based on LP256 */
	if (md_vid == CHA_VER_VID_MD_LP256)
		md_limit = SHA256_DIGEST_SIZE;

	INIT_LIST_HEAD(&hash_list);

	/* register crypto algorithms the device supports */
	for (i = 0; i < ARRAY_SIZE(driver_hash); i++) {
		struct caam_hash_alg *t_alg;
		struct caam_hash_template *alg = driver_hash + i;

		/* If MD size is not supported by device, skip registration */
		if (is_mdha(alg->alg_type) &&
		    alg->template_ahash.halg.digestsize > md_limit)
			continue;

		/* register hmac version */
		t_alg = caam_hash_alloc(alg, true);
		if (IS_ERR(t_alg)) {
			err = PTR_ERR(t_alg);
			pr_warn("%s alg allocation failed\n",
				alg->hmac_driver_name);
			continue;
		}

		err = crypto_register_ahash(&t_alg->ahash_alg);
		if (err) {
			pr_warn("%s alg registration failed: %d\n",
				t_alg->ahash_alg.halg.base.cra_driver_name,
				err);
			kfree(t_alg);
		} else
			list_add_tail(&t_alg->entry, &hash_list);

		if ((alg->alg_type & OP_ALG_ALGSEL_MASK) == OP_ALG_ALGSEL_AES)
			continue;

		/* register unkeyed version */
		t_alg = caam_hash_alloc(alg, false);
		if (IS_ERR(t_alg)) {
			err = PTR_ERR(t_alg);
			pr_warn("%s alg allocation failed\n", alg->driver_name);
			continue;
		}

		err = crypto_register_ahash(&t_alg->ahash_alg);
		if (err) {
			pr_warn("%s alg registration failed: %d\n",
				t_alg->ahash_alg.halg.base.cra_driver_name,
				err);
			kfree(t_alg);
		} else
			list_add_tail(&t_alg->entry, &hash_list);
	}

	return err;
}