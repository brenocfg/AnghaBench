#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * ports; int /*<<< orphan*/ * rxq_ids; } ;
struct uld_ctx {TYPE_2__ lldi; } ;
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct crypto_ablkcipher {int dummy; } ;
struct chcr_dev {int dummy; } ;
struct TYPE_5__ {int flags; } ;
struct ablkcipher_request {TYPE_1__ base; } ;
struct TYPE_7__ {size_t rx_qidx; int /*<<< orphan*/  tx_qidx; struct chcr_dev* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHCR_DECRYPT_OP ; 
 int /*<<< orphan*/  CPL_PRIORITY_DATA ; 
 int CRYPTO_TFM_REQ_MAY_BACKLOG ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int ENOSPC ; 
 int ENXIO ; 
 struct uld_ctx* ULD_CTX (TYPE_3__*) ; 
 TYPE_3__* c_ctx (struct crypto_ablkcipher*) ; 
 int chcr_inc_wrcount (struct chcr_dev*) ; 
 int /*<<< orphan*/  chcr_send_wr (struct sk_buff*) ; 
 struct crypto_ablkcipher* crypto_ablkcipher_reqtfm (struct ablkcipher_request*) ; 
 int /*<<< orphan*/  cxgb4_is_crypto_q_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_cipher (struct ablkcipher_request*,int /*<<< orphan*/ ,struct sk_buff**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_wr_txq (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int chcr_aes_decrypt(struct ablkcipher_request *req)
{
	struct crypto_ablkcipher *tfm = crypto_ablkcipher_reqtfm(req);
	struct uld_ctx *u_ctx = ULD_CTX(c_ctx(tfm));
	struct chcr_dev *dev = c_ctx(tfm)->dev;
	struct sk_buff *skb = NULL;
	int err, isfull = 0;

	err = chcr_inc_wrcount(dev);
	if (err)
		return -ENXIO;

	if (unlikely(cxgb4_is_crypto_q_full(u_ctx->lldi.ports[0],
					    c_ctx(tfm)->tx_qidx))) {
		isfull = 1;
		if (!(req->base.flags & CRYPTO_TFM_REQ_MAY_BACKLOG))
			return -ENOSPC;
	}

	err = process_cipher(req, u_ctx->lldi.rxq_ids[c_ctx(tfm)->rx_qidx],
			     &skb, CHCR_DECRYPT_OP);
	if (err || !skb)
		return err;
	skb->dev = u_ctx->lldi.ports[0];
	set_wr_txq(skb, CPL_PRIORITY_DATA, c_ctx(tfm)->tx_qidx);
	chcr_send_wr(skb);
	return isfull ? -EBUSY : -EINPROGRESS;
}