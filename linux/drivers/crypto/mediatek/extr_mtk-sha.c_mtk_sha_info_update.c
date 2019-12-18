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
struct mtk_sha_info {int /*<<< orphan*/ * ctrl; int /*<<< orphan*/ * cmd; } ;
struct mtk_sha_reqctx {int ct_dma; int tfm_dma; scalar_t__ digcnt; int /*<<< orphan*/  ct_hdr; struct mtk_sha_info info; } ;
struct mtk_sha_rec {int /*<<< orphan*/  req; } ;
struct mtk_cryp {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int /*<<< orphan*/  SHA_DATA_LEN_MSK ; 
 int /*<<< orphan*/  SHA_TFM_START ; 
 struct mtk_sha_reqctx* ahash_request_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int dma_map_single (int /*<<< orphan*/ ,struct mtk_sha_info*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_mapping_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_sha_info_update(struct mtk_cryp *cryp,
			       struct mtk_sha_rec *sha,
			       size_t len1, size_t len2)
{
	struct mtk_sha_reqctx *ctx = ahash_request_ctx(sha->req);
	struct mtk_sha_info *info = &ctx->info;

	ctx->ct_hdr &= ~SHA_DATA_LEN_MSK;
	ctx->ct_hdr |= cpu_to_le32(len1 + len2);
	info->cmd[0] &= ~SHA_DATA_LEN_MSK;
	info->cmd[0] |= cpu_to_le32(len1 + len2);

	/* Setting SHA_TFM_START only for the first iteration */
	if (ctx->digcnt)
		info->ctrl[0] &= ~SHA_TFM_START;

	ctx->digcnt += len1;

	ctx->ct_dma = dma_map_single(cryp->dev, info, sizeof(*info),
				     DMA_BIDIRECTIONAL);
	if (unlikely(dma_mapping_error(cryp->dev, ctx->ct_dma))) {
		dev_err(cryp->dev, "dma %zu bytes error\n", sizeof(*info));
		return -EINVAL;
	}

	ctx->tfm_dma = ctx->ct_dma + sizeof(info->ctrl) + sizeof(info->cmd);

	return 0;
}