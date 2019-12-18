#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device {int dummy; } ;
struct caam_drv_private {int era; TYPE_3__* ctrl; } ;
struct TYPE_10__ {int /*<<< orphan*/  cra_driver_name; } ;
struct TYPE_11__ {TYPE_4__ base; } ;
struct TYPE_12__ {int registered; TYPE_5__ akcipher; } ;
struct TYPE_8__ {int /*<<< orphan*/  pkha; } ;
struct TYPE_7__ {int /*<<< orphan*/  cha_num_ls; } ;
struct TYPE_9__ {TYPE_2__ vreg; TYPE_1__ perfmon; } ;

/* Variables and functions */
 scalar_t__ CAAM_RSA_MAX_INPUT_SIZE ; 
 int CHA_ID_LS_PK_MASK ; 
 int CHA_ID_LS_PK_SHIFT ; 
 int CHA_VER_NUM_MASK ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 TYPE_6__ caam_rsa ; 
 int crypto_register_akcipher (TYPE_5__*) ; 
 struct caam_drv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int /*<<< orphan*/ ) ; 
 int init_done ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (scalar_t__,int) ; 
 int rd_reg32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zero_buffer ; 

int caam_pkc_init(struct device *ctrldev)
{
	struct caam_drv_private *priv = dev_get_drvdata(ctrldev);
	u32 pk_inst;
	int err;
	init_done = false;

	/* Determine public key hardware accelerator presence. */
	if (priv->era < 10)
		pk_inst = (rd_reg32(&priv->ctrl->perfmon.cha_num_ls) &
			   CHA_ID_LS_PK_MASK) >> CHA_ID_LS_PK_SHIFT;
	else
		pk_inst = rd_reg32(&priv->ctrl->vreg.pkha) & CHA_VER_NUM_MASK;

	/* Do not register algorithms if PKHA is not present. */
	if (!pk_inst)
		return 0;

	/* allocate zero buffer, used for padding input */
	zero_buffer = kzalloc(CAAM_RSA_MAX_INPUT_SIZE - 1, GFP_DMA |
			      GFP_KERNEL);
	if (!zero_buffer)
		return -ENOMEM;

	err = crypto_register_akcipher(&caam_rsa.akcipher);

	if (err) {
		kfree(zero_buffer);
		dev_warn(ctrldev, "%s alg registration failed\n",
			 caam_rsa.akcipher.base.cra_driver_name);
	} else {
		init_done = true;
		caam_rsa.registered = true;
		dev_info(ctrldev, "caam pkc algorithms registered in /proc/crypto\n");
	}

	return err;
}