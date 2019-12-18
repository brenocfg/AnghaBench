#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct cc_drvdata {scalar_t__ mlli_sram_addr; } ;
struct aead_request {scalar_t__ src; scalar_t__ dst; } ;
struct TYPE_8__ {int mlli_nents; scalar_t__ sram_addr; } ;
struct TYPE_7__ {int mlli_nents; scalar_t__ sram_addr; } ;
struct TYPE_6__ {int mlli_nents; scalar_t__ sram_addr; } ;
struct TYPE_5__ {scalar_t__ op_type; } ;
struct aead_req_ctx {scalar_t__ assoc_buff_type; scalar_t__ data_buff_type; TYPE_4__ dst; TYPE_3__ assoc; int /*<<< orphan*/  is_single_pass; TYPE_2__ src; TYPE_1__ gen_ctx; } ;

/* Variables and functions */
 scalar_t__ CC_DMA_BUF_MLLI ; 
 scalar_t__ DRV_CRYPTO_DIRECTION_DECRYPT ; 
 int LLI_ENTRY_BYTE_SIZE ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 

__attribute__((used)) static void cc_update_aead_mlli_nents(struct cc_drvdata *drvdata,
				      struct aead_request *req)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	u32 curr_mlli_size = 0;

	if (areq_ctx->assoc_buff_type == CC_DMA_BUF_MLLI) {
		areq_ctx->assoc.sram_addr = drvdata->mlli_sram_addr;
		curr_mlli_size = areq_ctx->assoc.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
	}

	if (areq_ctx->data_buff_type == CC_DMA_BUF_MLLI) {
		/*Inplace case dst nents equal to src nents*/
		if (req->src == req->dst) {
			areq_ctx->dst.mlli_nents = areq_ctx->src.mlli_nents;
			areq_ctx->src.sram_addr = drvdata->mlli_sram_addr +
								curr_mlli_size;
			areq_ctx->dst.sram_addr = areq_ctx->src.sram_addr;
			if (!areq_ctx->is_single_pass)
				areq_ctx->assoc.mlli_nents +=
					areq_ctx->src.mlli_nents;
		} else {
			if (areq_ctx->gen_ctx.op_type ==
					DRV_CRYPTO_DIRECTION_DECRYPT) {
				areq_ctx->src.sram_addr =
						drvdata->mlli_sram_addr +
								curr_mlli_size;
				areq_ctx->dst.sram_addr =
						areq_ctx->src.sram_addr +
						areq_ctx->src.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
				if (!areq_ctx->is_single_pass)
					areq_ctx->assoc.mlli_nents +=
						areq_ctx->src.mlli_nents;
			} else {
				areq_ctx->dst.sram_addr =
						drvdata->mlli_sram_addr +
								curr_mlli_size;
				areq_ctx->src.sram_addr =
						areq_ctx->dst.sram_addr +
						areq_ctx->dst.mlli_nents *
						LLI_ENTRY_BYTE_SIZE;
				if (!areq_ctx->is_single_pass)
					areq_ctx->assoc.mlli_nents +=
						areq_ctx->dst.mlli_nents;
			}
		}
	}
}