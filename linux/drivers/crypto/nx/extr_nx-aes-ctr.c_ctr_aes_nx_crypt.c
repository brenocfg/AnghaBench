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
struct scatterlist {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  processed_byte_count; } ;
struct TYPE_8__ {int /*<<< orphan*/  cv; } ;
struct TYPE_7__ {int /*<<< orphan*/  iv; } ;
struct TYPE_9__ {TYPE_2__ aes_cbc; TYPE_1__ aes_ctr; } ;
struct nx_csbcpb {TYPE_4__ csb; TYPE_3__ cpb; } ;
struct TYPE_12__ {int /*<<< orphan*/  outlen; int /*<<< orphan*/  inlen; } ;
struct nx_crypto_ctx {int /*<<< orphan*/  lock; TYPE_5__* stats; TYPE_6__ op; struct nx_csbcpb* csbcpb; } ;
struct blkcipher_desc {int flags; int /*<<< orphan*/  info; int /*<<< orphan*/  tfm; } ;
struct TYPE_11__ {int /*<<< orphan*/  aes_bytes; int /*<<< orphan*/  aes_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  AES_BLOCK_SIZE ; 
 int CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EINVAL ; 
 int /*<<< orphan*/  atomic64_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct nx_crypto_ctx* crypto_blkcipher_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nx_build_sg_lists (struct nx_crypto_ctx*,struct blkcipher_desc*,struct scatterlist*,struct scatterlist*,unsigned int*,unsigned int,int /*<<< orphan*/ ) ; 
 int nx_hcall_sync (struct nx_crypto_ctx*,TYPE_6__*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ctr_aes_nx_crypt(struct blkcipher_desc *desc,
			    struct scatterlist    *dst,
			    struct scatterlist    *src,
			    unsigned int           nbytes)
{
	struct nx_crypto_ctx *nx_ctx = crypto_blkcipher_ctx(desc->tfm);
	struct nx_csbcpb *csbcpb = nx_ctx->csbcpb;
	unsigned long irq_flags;
	unsigned int processed = 0, to_process;
	int rc;

	spin_lock_irqsave(&nx_ctx->lock, irq_flags);

	do {
		to_process = nbytes - processed;

		rc = nx_build_sg_lists(nx_ctx, desc, dst, src, &to_process,
				       processed, csbcpb->cpb.aes_ctr.iv);
		if (rc)
			goto out;

		if (!nx_ctx->op.inlen || !nx_ctx->op.outlen) {
			rc = -EINVAL;
			goto out;
		}

		rc = nx_hcall_sync(nx_ctx, &nx_ctx->op,
				   desc->flags & CRYPTO_TFM_REQ_MAY_SLEEP);
		if (rc)
			goto out;

		memcpy(desc->info, csbcpb->cpb.aes_cbc.cv, AES_BLOCK_SIZE);

		atomic_inc(&(nx_ctx->stats->aes_ops));
		atomic64_add(csbcpb->csb.processed_byte_count,
			     &(nx_ctx->stats->aes_bytes));

		processed += to_process;
	} while (processed < nbytes);
out:
	spin_unlock_irqrestore(&nx_ctx->lock, irq_flags);
	return rc;
}