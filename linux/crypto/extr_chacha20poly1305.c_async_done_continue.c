#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct chachapoly_req_ctx {int /*<<< orphan*/  flags; } ;
struct aead_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_TFM_REQ_MAY_SLEEP ; 
 int EBUSY ; 
 int EINPROGRESS ; 
 int /*<<< orphan*/  aead_request_complete (struct aead_request*,int) ; 
 struct chachapoly_req_ctx* aead_request_ctx (struct aead_request*) ; 

__attribute__((used)) static inline void async_done_continue(struct aead_request *req, int err,
				       int (*cont)(struct aead_request *))
{
	if (!err) {
		struct chachapoly_req_ctx *rctx = aead_request_ctx(req);

		rctx->flags &= ~CRYPTO_TFM_REQ_MAY_SLEEP;
		err = cont(req);
	}

	if (err != -EINPROGRESS && err != -EBUSY)
		aead_request_complete(req, err);
}