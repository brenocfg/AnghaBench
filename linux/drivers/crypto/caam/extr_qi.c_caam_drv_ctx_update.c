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
typedef  int u32 ;
struct qman_fq {int dummy; } ;
struct device {int dummy; } ;
struct caam_drv_ctx {struct qman_fq* req_fq; int /*<<< orphan*/  context_a; int /*<<< orphan*/  sh_desc; void** prehdr; int /*<<< orphan*/  rsp_fq; struct device* qidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct qman_fq*) ; 
 int MAX_SDLEN ; 
 int PREHDR_ABS ; 
 int PREHDR_RSLS_SHIFT ; 
 int PTR_ERR (struct qman_fq*) ; 
 void* cpu_to_caam32 (int) ; 
 struct qman_fq* create_caam_req_fq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_bytes (int*) ; 
 int desc_len (int*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  dma_sync_single_for_device (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int empty_caam_fq (struct qman_fq*) ; 
 scalar_t__ kill_fq (struct device*,struct qman_fq*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int qman_schedule_fq (struct qman_fq*) ; 

int caam_drv_ctx_update(struct caam_drv_ctx *drv_ctx, u32 *sh_desc)
{
	int ret;
	u32 num_words;
	struct qman_fq *new_fq, *old_fq;
	struct device *qidev = drv_ctx->qidev;

	num_words = desc_len(sh_desc);
	if (num_words > MAX_SDLEN) {
		dev_err(qidev, "Invalid descriptor len: %d words\n", num_words);
		return -EINVAL;
	}

	/* Note down older req FQ */
	old_fq = drv_ctx->req_fq;

	/* Create a new req FQ in parked state */
	new_fq = create_caam_req_fq(drv_ctx->qidev, drv_ctx->rsp_fq,
				    drv_ctx->context_a, 0);
	if (IS_ERR(new_fq)) {
		dev_err(qidev, "FQ allocation for shdesc update failed\n");
		return PTR_ERR(new_fq);
	}

	/* Hook up new FQ to context so that new requests keep queuing */
	drv_ctx->req_fq = new_fq;

	/* Empty and remove the older FQ */
	ret = empty_caam_fq(old_fq);
	if (ret) {
		dev_err(qidev, "Old CAAM FQ empty failed: %d\n", ret);

		/* We can revert to older FQ */
		drv_ctx->req_fq = old_fq;

		if (kill_fq(qidev, new_fq))
			dev_warn(qidev, "New CAAM FQ kill failed\n");

		return ret;
	}

	/*
	 * Re-initialise pre-header. Set RSLS and SDLEN.
	 * Update the shared descriptor for driver context.
	 */
	drv_ctx->prehdr[0] = cpu_to_caam32((1 << PREHDR_RSLS_SHIFT) |
					   num_words);
	drv_ctx->prehdr[1] = cpu_to_caam32(PREHDR_ABS);
	memcpy(drv_ctx->sh_desc, sh_desc, desc_bytes(sh_desc));
	dma_sync_single_for_device(qidev, drv_ctx->context_a,
				   sizeof(drv_ctx->sh_desc) +
				   sizeof(drv_ctx->prehdr),
				   DMA_BIDIRECTIONAL);

	/* Put the new FQ in scheduled state */
	ret = qman_schedule_fq(new_fq);
	if (ret) {
		dev_err(qidev, "Fail to sched new CAAM FQ, ecode = %d\n", ret);

		/*
		 * We can kill new FQ and revert to old FQ.
		 * Since the desc is already modified, it is success case
		 */

		drv_ctx->req_fq = old_fq;

		if (kill_fq(qidev, new_fq))
			dev_warn(qidev, "New CAAM FQ kill failed\n");
	} else if (kill_fq(qidev, old_fq)) {
		dev_warn(qidev, "Old CAAM FQ kill failed\n");
	}

	return 0;
}