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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct caam_rng_ctx {int /*<<< orphan*/  sh_desc_dma; int /*<<< orphan*/  sh_desc; struct buf_data* bufs; struct device* jrdev; } ;
struct buf_data {int /*<<< orphan*/  addr; int /*<<< orphan*/  buf; int /*<<< orphan*/ * hw_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int ENOMEM ; 
 int HDR_REVERSE ; 
 int HDR_SHARE_DEFER ; 
 int /*<<< orphan*/  RN_BUF_SIZE ; 
 int /*<<< orphan*/  append_seq_out_ptr_intlen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ *) ; 
 int desc_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_job_desc_shared (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int rng_create_job_desc(struct caam_rng_ctx *ctx, int buf_id)
{
	struct device *jrdev = ctx->jrdev;
	struct buf_data *bd = &ctx->bufs[buf_id];
	u32 *desc = bd->hw_desc;
	int sh_len = desc_len(ctx->sh_desc);

	init_job_desc_shared(desc, ctx->sh_desc_dma, sh_len, HDR_SHARE_DEFER |
			     HDR_REVERSE);

	bd->addr = dma_map_single(jrdev, bd->buf, RN_BUF_SIZE, DMA_FROM_DEVICE);
	if (dma_mapping_error(jrdev, bd->addr)) {
		dev_err(jrdev, "unable to map dst\n");
		return -ENOMEM;
	}

	append_seq_out_ptr_intlen(desc, bd->addr, RN_BUF_SIZE, 0);

	print_hex_dump_debug("rng job desc@: ", DUMP_PREFIX_ADDRESS, 16, 4,
			     desc, desc_bytes(desc), 1);

	return 0;
}