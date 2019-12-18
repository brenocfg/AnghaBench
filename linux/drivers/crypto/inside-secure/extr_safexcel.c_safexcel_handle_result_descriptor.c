#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int rd_offset; } ;
struct safexcel_crypto_priv {TYPE_2__* ring; TYPE_1__ config; int /*<<< orphan*/  dev; } ;
struct safexcel_context {int (* handle_result ) (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int*,int*) ;} ;
struct crypto_async_request {int /*<<< orphan*/  (* complete ) (struct crypto_async_request*,int) ;int /*<<< orphan*/  tfm; } ;
struct TYPE_4__ {int busy; int /*<<< orphan*/  lock; scalar_t__ requests; } ;

/* Variables and functions */
 scalar_t__ EIP197_HIA_RDR (struct safexcel_crypto_priv*,int) ; 
 scalar_t__ EIP197_HIA_xDR_PROC_COUNT ; 
 int EIP197_xDR_PROC_xD_COUNT (int) ; 
 int EIP197_xDR_PROC_xD_PKT (int) ; 
 int EIP197_xDR_PROC_xD_PKT_MASK ; 
 int EIP197_xDR_PROC_xD_PKT_OFFSET ; 
 struct safexcel_context* crypto_tfm_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int readl (scalar_t__) ; 
 struct crypto_async_request* safexcel_rdr_req_get (struct safexcel_crypto_priv*,int) ; 
 int /*<<< orphan*/  safexcel_try_push_requests (struct safexcel_crypto_priv*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct safexcel_crypto_priv*,int,struct crypto_async_request*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct crypto_async_request*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static inline void safexcel_handle_result_descriptor(struct safexcel_crypto_priv *priv,
						     int ring)
{
	struct crypto_async_request *req;
	struct safexcel_context *ctx;
	int ret, i, nreq, ndesc, tot_descs, handled = 0;
	bool should_complete;

handle_results:
	tot_descs = 0;

	nreq = readl(EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_PROC_COUNT);
	nreq >>= EIP197_xDR_PROC_xD_PKT_OFFSET;
	nreq &= EIP197_xDR_PROC_xD_PKT_MASK;
	if (!nreq)
		goto requests_left;

	for (i = 0; i < nreq; i++) {
		req = safexcel_rdr_req_get(priv, ring);

		ctx = crypto_tfm_ctx(req->tfm);
		ndesc = ctx->handle_result(priv, ring, req,
					   &should_complete, &ret);
		if (ndesc < 0) {
			dev_err(priv->dev, "failed to handle result (%d)\n",
				ndesc);
			goto acknowledge;
		}

		if (should_complete) {
			local_bh_disable();
			req->complete(req, ret);
			local_bh_enable();
		}

		tot_descs += ndesc;
		handled++;
	}

acknowledge:
	if (i)
		writel(EIP197_xDR_PROC_xD_PKT(i) |
		       EIP197_xDR_PROC_xD_COUNT(tot_descs * priv->config.rd_offset),
		       EIP197_HIA_RDR(priv, ring) + EIP197_HIA_xDR_PROC_COUNT);

	/* If the number of requests overflowed the counter, try to proceed more
	 * requests.
	 */
	if (nreq == EIP197_xDR_PROC_xD_PKT_MASK)
		goto handle_results;

requests_left:
	spin_lock_bh(&priv->ring[ring].lock);

	priv->ring[ring].requests -= handled;
	safexcel_try_push_requests(priv, ring);

	if (!priv->ring[ring].requests)
		priv->ring[ring].busy = false;

	spin_unlock_bh(&priv->ring[ring].lock);
}