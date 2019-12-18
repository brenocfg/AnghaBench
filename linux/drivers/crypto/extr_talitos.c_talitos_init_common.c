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
struct talitos_private {int num_channels; int /*<<< orphan*/  last_chan; } ;
struct talitos_ctx {int ch; int /*<<< orphan*/  desc_hdr_template; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_hdr_template; } ;
struct talitos_crypto_alg {TYPE_1__ algt; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_HDR_DONE_NOTIFY ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 struct talitos_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int talitos_init_common(struct talitos_ctx *ctx,
			       struct talitos_crypto_alg *talitos_alg)
{
	struct talitos_private *priv;

	/* update context with ptr to dev */
	ctx->dev = talitos_alg->dev;

	/* assign SEC channel to tfm in round-robin fashion */
	priv = dev_get_drvdata(ctx->dev);
	ctx->ch = atomic_inc_return(&priv->last_chan) &
		  (priv->num_channels - 1);

	/* copy descriptor header template value */
	ctx->desc_hdr_template = talitos_alg->algt.desc_hdr_template;

	/* select done notification */
	ctx->desc_hdr_template |= DESC_HDR_DONE_NOTIFY;

	return 0;
}