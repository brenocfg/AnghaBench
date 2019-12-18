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
struct mv_cesa_engine {int /*<<< orphan*/  load; scalar_t__ regs; } ;
struct TYPE_11__ {TYPE_4__* last; } ;
struct TYPE_12__ {TYPE_5__ chain; struct mv_cesa_engine* engine; } ;
struct mv_cesa_ahash_req {void** state; scalar_t__ algo_le; scalar_t__ last_req; TYPE_6__ base; } ;
struct crypto_async_request {int dummy; } ;
struct ahash_request {int /*<<< orphan*/  nbytes; scalar_t__ result; } ;
typedef  void* __le32 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_10__ {int flags; TYPE_3__* op; } ;
struct TYPE_7__ {void** hash; } ;
struct TYPE_8__ {TYPE_1__ hash; } ;
struct TYPE_9__ {TYPE_2__ ctx; } ;

/* Variables and functions */
 scalar_t__ CESA_DMA_REQ ; 
 scalar_t__ CESA_IVDIG (int) ; 
 int CESA_TDMA_RESULT ; 
 int CESA_TDMA_TYPE_MSK ; 
 struct ahash_request* ahash_request_cast (struct crypto_async_request*) ; 
 struct mv_cesa_ahash_req* ahash_request_ctx (struct ahash_request*) ; 
 int /*<<< orphan*/  atomic_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_be32 (void*) ; 
 void* cpu_to_le32 (void*) ; 
 unsigned int crypto_ahash_digestsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crypto_ahash_reqtfm (struct ahash_request*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void**,unsigned int) ; 
 scalar_t__ mv_cesa_req_get_type (TYPE_6__*) ; 
 void* readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void mv_cesa_ahash_complete(struct crypto_async_request *req)
{
	struct ahash_request *ahashreq = ahash_request_cast(req);
	struct mv_cesa_ahash_req *creq = ahash_request_ctx(ahashreq);
	struct mv_cesa_engine *engine = creq->base.engine;
	unsigned int digsize;
	int i;

	digsize = crypto_ahash_digestsize(crypto_ahash_reqtfm(ahashreq));

	if (mv_cesa_req_get_type(&creq->base) == CESA_DMA_REQ &&
	    (creq->base.chain.last->flags & CESA_TDMA_TYPE_MSK) == CESA_TDMA_RESULT) {
		__le32 *data = NULL;

		/*
		 * Result is already in the correct endianess when the SA is
		 * used
		 */
		data = creq->base.chain.last->op->ctx.hash.hash;
		for (i = 0; i < digsize / 4; i++)
			creq->state[i] = cpu_to_le32(data[i]);

		memcpy(ahashreq->result, data, digsize);
	} else {
		for (i = 0; i < digsize / 4; i++)
			creq->state[i] = readl_relaxed(engine->regs +
						       CESA_IVDIG(i));
		if (creq->last_req) {
			/*
			* Hardware's MD5 digest is in little endian format, but
			* SHA in big endian format
			*/
			if (creq->algo_le) {
				__le32 *result = (void *)ahashreq->result;

				for (i = 0; i < digsize / 4; i++)
					result[i] = cpu_to_le32(creq->state[i]);
			} else {
				__be32 *result = (void *)ahashreq->result;

				for (i = 0; i < digsize / 4; i++)
					result[i] = cpu_to_be32(creq->state[i]);
			}
		}
	}

	atomic_sub(ahashreq->nbytes, &engine->load);
}