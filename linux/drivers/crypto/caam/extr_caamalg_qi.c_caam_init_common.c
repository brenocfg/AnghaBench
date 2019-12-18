#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct caam_drv_private {int era; } ;
struct TYPE_8__ {int algtype; } ;
struct TYPE_7__ {int algtype; } ;
struct caam_ctx {int /*<<< orphan*/ ** drv_ctx; int /*<<< orphan*/  lock; struct device* qidev; TYPE_2__ adata; TYPE_1__ cdata; TYPE_3__* jrdev; int /*<<< orphan*/  key_dma; int /*<<< orphan*/  dir; int /*<<< orphan*/  key; } ;
struct caam_alg_entry {int class1_alg_type; int class2_alg_type; } ;
struct TYPE_9__ {struct device* parent; } ;

/* Variables and functions */
 size_t DECRYPT ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 size_t ENCRYPT ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (TYPE_3__*) ; 
 int OP_TYPE_CLASS1_ALG ; 
 int OP_TYPE_CLASS2_ALG ; 
 int PTR_ERR (TYPE_3__*) ; 
 TYPE_3__* caam_jr_alloc () ; 
 int /*<<< orphan*/  caam_jr_free (TYPE_3__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct caam_drv_private* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int caam_init_common(struct caam_ctx *ctx, struct caam_alg_entry *caam,
			    bool uses_dkp)
{
	struct caam_drv_private *priv;
	struct device *dev;

	/*
	 * distribute tfms across job rings to ensure in-order
	 * crypto request processing per tfm
	 */
	ctx->jrdev = caam_jr_alloc();
	if (IS_ERR(ctx->jrdev)) {
		pr_err("Job Ring Device allocation for transform failed\n");
		return PTR_ERR(ctx->jrdev);
	}

	dev = ctx->jrdev->parent;
	priv = dev_get_drvdata(dev);
	if (priv->era >= 6 && uses_dkp)
		ctx->dir = DMA_BIDIRECTIONAL;
	else
		ctx->dir = DMA_TO_DEVICE;

	ctx->key_dma = dma_map_single(dev, ctx->key, sizeof(ctx->key),
				      ctx->dir);
	if (dma_mapping_error(dev, ctx->key_dma)) {
		dev_err(dev, "unable to map key\n");
		caam_jr_free(ctx->jrdev);
		return -ENOMEM;
	}

	/* copy descriptor header template value */
	ctx->cdata.algtype = OP_TYPE_CLASS1_ALG | caam->class1_alg_type;
	ctx->adata.algtype = OP_TYPE_CLASS2_ALG | caam->class2_alg_type;

	ctx->qidev = dev;

	spin_lock_init(&ctx->lock);
	ctx->drv_ctx[ENCRYPT] = NULL;
	ctx->drv_ctx[DECRYPT] = NULL;

	return 0;
}