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
typedef  scalar_t__ u32 ;
struct scatterlist {scalar_t__ length; } ;
struct device {int dummy; } ;
struct crypto_aead {int dummy; } ;
struct cc_drvdata {int dummy; } ;
struct buffer_array {int dummy; } ;
struct aead_request {unsigned int cryptlen; struct scatterlist* dst; struct scatterlist* src; } ;
struct TYPE_6__ {scalar_t__ nents; } ;
struct TYPE_5__ {scalar_t__ nents; } ;
struct TYPE_4__ {int op_type; } ;
struct aead_req_ctx {unsigned int req_authsize; unsigned int assoclen; int is_gcm4543; int /*<<< orphan*/  data_buff_type; scalar_t__ dst_offset; TYPE_3__ dst; struct scatterlist* dst_sgl; scalar_t__ src_offset; TYPE_2__ src; struct scatterlist* src_sgl; TYPE_1__ gen_ctx; } ;
typedef  enum drv_crypto_direction { ____Placeholder_drv_crypto_direction } drv_crypto_direction ;

/* Variables and functions */
 int /*<<< orphan*/  CC_DMA_BUF_DLLI ; 
 int /*<<< orphan*/  CC_DMA_BUF_MLLI ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int DRV_CRYPTO_DIRECTION_ENCRYPT ; 
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ LLI_MAX_NUM_OF_DATA_ENTRIES ; 
 struct aead_req_ctx* aead_request_ctx (struct aead_request*) ; 
 scalar_t__ cc_get_sgl_nents (struct device*,struct scatterlist*,unsigned int,unsigned int*) ; 
 int cc_map_sg (struct device*,struct scatterlist*,unsigned int,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  cc_prepare_aead_data_dlli (struct aead_request*,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  cc_prepare_aead_data_mlli (struct cc_drvdata*,struct aead_request*,struct buffer_array*,unsigned int*,unsigned int*,int) ; 
 scalar_t__ crypto_aead_ivsize (struct crypto_aead*) ; 
 struct crypto_aead* crypto_aead_reqtfm (struct aead_request*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,scalar_t__) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int cc_aead_chain_data(struct cc_drvdata *drvdata,
			      struct aead_request *req,
			      struct buffer_array *sg_data,
			      bool is_last_table, bool do_chain)
{
	struct aead_req_ctx *areq_ctx = aead_request_ctx(req);
	struct device *dev = drvdata_to_dev(drvdata);
	enum drv_crypto_direction direct = areq_ctx->gen_ctx.op_type;
	unsigned int authsize = areq_ctx->req_authsize;
	unsigned int src_last_bytes = 0, dst_last_bytes = 0;
	int rc = 0;
	u32 src_mapped_nents = 0, dst_mapped_nents = 0;
	u32 offset = 0;
	/* non-inplace mode */
	unsigned int size_for_map = areq_ctx->assoclen + req->cryptlen;
	struct crypto_aead *tfm = crypto_aead_reqtfm(req);
	u32 sg_index = 0;
	bool is_gcm4543 = areq_ctx->is_gcm4543;
	u32 size_to_skip = areq_ctx->assoclen;
	struct scatterlist *sgl;

	if (is_gcm4543)
		size_to_skip += crypto_aead_ivsize(tfm);

	offset = size_to_skip;

	if (!sg_data)
		return -EINVAL;

	areq_ctx->src_sgl = req->src;
	areq_ctx->dst_sgl = req->dst;

	if (is_gcm4543)
		size_for_map += crypto_aead_ivsize(tfm);

	size_for_map += (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) ?
			authsize : 0;
	src_mapped_nents = cc_get_sgl_nents(dev, req->src, size_for_map,
					    &src_last_bytes);
	sg_index = areq_ctx->src_sgl->length;
	//check where the data starts
	while (sg_index <= size_to_skip) {
		src_mapped_nents--;
		offset -= areq_ctx->src_sgl->length;
		sgl = sg_next(areq_ctx->src_sgl);
		if (!sgl)
			break;
		areq_ctx->src_sgl = sgl;
		sg_index += areq_ctx->src_sgl->length;
	}
	if (src_mapped_nents > LLI_MAX_NUM_OF_DATA_ENTRIES) {
		dev_err(dev, "Too many fragments. current %d max %d\n",
			src_mapped_nents, LLI_MAX_NUM_OF_DATA_ENTRIES);
		return -ENOMEM;
	}

	areq_ctx->src.nents = src_mapped_nents;

	areq_ctx->src_offset = offset;

	if (req->src != req->dst) {
		size_for_map = areq_ctx->assoclen + req->cryptlen;
		size_for_map += (direct == DRV_CRYPTO_DIRECTION_ENCRYPT) ?
				authsize : 0;
		if (is_gcm4543)
			size_for_map += crypto_aead_ivsize(tfm);

		rc = cc_map_sg(dev, req->dst, size_for_map, DMA_BIDIRECTIONAL,
			       &areq_ctx->dst.nents,
			       LLI_MAX_NUM_OF_DATA_ENTRIES, &dst_last_bytes,
			       &dst_mapped_nents);
		if (rc)
			goto chain_data_exit;
	}

	dst_mapped_nents = cc_get_sgl_nents(dev, req->dst, size_for_map,
					    &dst_last_bytes);
	sg_index = areq_ctx->dst_sgl->length;
	offset = size_to_skip;

	//check where the data starts
	while (sg_index <= size_to_skip) {
		dst_mapped_nents--;
		offset -= areq_ctx->dst_sgl->length;
		sgl = sg_next(areq_ctx->dst_sgl);
		if (!sgl)
			break;
		areq_ctx->dst_sgl = sgl;
		sg_index += areq_ctx->dst_sgl->length;
	}
	if (dst_mapped_nents > LLI_MAX_NUM_OF_DATA_ENTRIES) {
		dev_err(dev, "Too many fragments. current %d max %d\n",
			dst_mapped_nents, LLI_MAX_NUM_OF_DATA_ENTRIES);
		return -ENOMEM;
	}
	areq_ctx->dst.nents = dst_mapped_nents;
	areq_ctx->dst_offset = offset;
	if (src_mapped_nents > 1 ||
	    dst_mapped_nents  > 1 ||
	    do_chain) {
		areq_ctx->data_buff_type = CC_DMA_BUF_MLLI;
		cc_prepare_aead_data_mlli(drvdata, req, sg_data,
					  &src_last_bytes, &dst_last_bytes,
					  is_last_table);
	} else {
		areq_ctx->data_buff_type = CC_DMA_BUF_DLLI;
		cc_prepare_aead_data_dlli(req, &src_last_bytes,
					  &dst_last_bytes);
	}

chain_data_exit:
	return rc;
}