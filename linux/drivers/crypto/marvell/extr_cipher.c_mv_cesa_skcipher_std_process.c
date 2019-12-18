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
typedef  int /*<<< orphan*/  u32 ;
struct skcipher_request {scalar_t__ cryptlen; int /*<<< orphan*/  dst; } ;
struct mv_cesa_skcipher_std_req {scalar_t__ offset; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {struct mv_cesa_engine* engine; } ;
struct mv_cesa_skcipher_req {int /*<<< orphan*/  dst_nents; TYPE_1__ base; struct mv_cesa_skcipher_std_req std; } ;
struct mv_cesa_engine {scalar_t__ sram; } ;

/* Variables and functions */
 scalar_t__ CESA_SA_DATA_SRAM_OFFSET ; 
 int EINPROGRESS ; 
 size_t sg_pcopy_from_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 struct mv_cesa_skcipher_req* skcipher_request_ctx (struct skcipher_request*) ; 

__attribute__((used)) static int mv_cesa_skcipher_std_process(struct skcipher_request *req,
					u32 status)
{
	struct mv_cesa_skcipher_req *creq = skcipher_request_ctx(req);
	struct mv_cesa_skcipher_std_req *sreq = &creq->std;
	struct mv_cesa_engine *engine = creq->base.engine;
	size_t len;

	len = sg_pcopy_from_buffer(req->dst, creq->dst_nents,
				   engine->sram + CESA_SA_DATA_SRAM_OFFSET,
				   sreq->size, sreq->offset);

	sreq->offset += len;
	if (sreq->offset < req->cryptlen)
		return -EINPROGRESS;

	return 0;
}