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
typedef  int u64 ;
struct safexcel_crypto_priv {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int control0; int /*<<< orphan*/  control1; } ;
struct safexcel_command_desc {TYPE_3__ control_data; } ;
struct safexcel_ahash_req {int processed; int state_sz; int digest; int hmac_zlen; int block_sz; scalar_t__ finish; int /*<<< orphan*/  state; } ;
struct TYPE_5__ {TYPE_1__* ctxr; } ;
struct safexcel_ahash_ctx {int alg; int /*<<< orphan*/  opad; TYPE_2__ base; struct safexcel_crypto_priv* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTEXT_CONTROL_DIGEST_CNT ; 
 int CONTEXT_CONTROL_DIGEST_HMAC ; 
 int CONTEXT_CONTROL_DIGEST_PRECOMPUTED ; 
 int CONTEXT_CONTROL_NO_FINISH_HASH ; 
 int CONTEXT_CONTROL_RESTART_HASH ; 
 int CONTEXT_CONTROL_SIZE (int) ; 
 int CONTEXT_CONTROL_TYPE_HASH_OUT ; 
 int EIP197_COUNTER_BLOCK_SIZE ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void safexcel_context_control(struct safexcel_ahash_ctx *ctx,
				     struct safexcel_ahash_req *req,
				     struct safexcel_command_desc *cdesc)
{
	struct safexcel_crypto_priv *priv = ctx->priv;
	u64 count = 0;

	cdesc->control_data.control0 |= ctx->alg;

	/*
	 * Copy the input digest if needed, and setup the context
	 * fields. Do this now as we need it to setup the first command
	 * descriptor.
	 */
	if (!req->processed) {
		/* First - and possibly only - block of basic hash only */
		if (req->finish) {
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_RESTART_HASH  |
				/* ensure its not 0! */
				CONTEXT_CONTROL_SIZE(1);
		} else {
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_TYPE_HASH_OUT  |
				CONTEXT_CONTROL_RESTART_HASH   |
				CONTEXT_CONTROL_NO_FINISH_HASH |
				/* ensure its not 0! */
				CONTEXT_CONTROL_SIZE(1);
		}
		return;
	}

	/* Hash continuation or HMAC, setup (inner) digest from state */
	memcpy(ctx->base.ctxr->data, req->state, req->state_sz);

	if (req->finish) {
		/* Compute digest count for hash/HMAC finish operations */
		if ((req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) ||
		    req->hmac_zlen || (req->processed != req->block_sz)) {
			count = req->processed / EIP197_COUNTER_BLOCK_SIZE;

			/* This is a hardware limitation, as the
			 * counter must fit into an u32. This represents
			 * a fairly big amount of input data, so we
			 * shouldn't see this.
			 */
			if (unlikely(count & 0xffffffff00000000ULL)) {
				dev_warn(priv->dev,
					 "Input data is too big\n");
				return;
			}
		}

		if ((req->digest == CONTEXT_CONTROL_DIGEST_PRECOMPUTED) ||
		    /* Special case: zero length HMAC */
		    req->hmac_zlen ||
		    /* PE HW < 4.4 cannot do HMAC continue, fake using hash */
		    (req->processed != req->block_sz)) {
			/* Basic hash continue operation, need digest + cnt */
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_SIZE((req->state_sz >> 2) + 1) |
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_DIGEST_PRECOMPUTED;
			/* For zero-len HMAC, don't finalize, already padded! */
			if (req->hmac_zlen)
				cdesc->control_data.control0 |=
					CONTEXT_CONTROL_NO_FINISH_HASH;
			cdesc->control_data.control1 |=
				CONTEXT_CONTROL_DIGEST_CNT;
			ctx->base.ctxr->data[req->state_sz >> 2] =
				cpu_to_le32(count);
			req->digest = CONTEXT_CONTROL_DIGEST_PRECOMPUTED;

			/* Clear zero-length HMAC flag for next operation! */
			req->hmac_zlen = false;
		} else { /* HMAC */
			/* Need outer digest for HMAC finalization */
			memcpy(ctx->base.ctxr->data + (req->state_sz >> 2),
			       ctx->opad, req->state_sz);

			/* Single pass HMAC - no digest count */
			cdesc->control_data.control0 |=
				CONTEXT_CONTROL_SIZE(req->state_sz >> 1) |
				CONTEXT_CONTROL_TYPE_HASH_OUT |
				CONTEXT_CONTROL_DIGEST_HMAC;
		}
	} else { /* Hash continuation, do not finish yet */
		cdesc->control_data.control0 |=
			CONTEXT_CONTROL_SIZE(req->state_sz >> 2) |
			CONTEXT_CONTROL_DIGEST_PRECOMPUTED |
			CONTEXT_CONTROL_TYPE_HASH_OUT |
			CONTEXT_CONTROL_NO_FINISH_HASH;
	}
}