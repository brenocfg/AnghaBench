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
struct caam_rng_ctx {int /*<<< orphan*/  sh_desc_dma; int /*<<< orphan*/ * sh_desc; struct device* jrdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DUMP_PREFIX_ADDRESS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  FIFOST_TYPE_RNGSTORE ; 
 int /*<<< orphan*/  HDR_SHARE_SERIAL ; 
 int OP_ALG_ALGSEL_RNG ; 
 int OP_TYPE_CLASS1_ALG ; 
 int /*<<< orphan*/  RN_BUF_SIZE ; 
 int /*<<< orphan*/  append_operation (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  append_seq_fifo_store (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_bytes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_sh_desc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump_debug (char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int rng_create_sh_desc(struct caam_rng_ctx *ctx)
{
	struct device *jrdev = ctx->jrdev;
	u32 *desc = ctx->sh_desc;

	init_sh_desc(desc, HDR_SHARE_SERIAL);

	/* Generate random bytes */
	append_operation(desc, OP_ALG_ALGSEL_RNG | OP_TYPE_CLASS1_ALG);

	/* Store bytes */
	append_seq_fifo_store(desc, RN_BUF_SIZE, FIFOST_TYPE_RNGSTORE);

	ctx->sh_desc_dma = dma_map_single(jrdev, desc, desc_bytes(desc),
					  DMA_TO_DEVICE);
	if (dma_mapping_error(jrdev, ctx->sh_desc_dma)) {
		dev_err(jrdev, "unable to map shared descriptor\n");
		return -ENOMEM;
	}

	print_hex_dump_debug("rng shdesc@: ", DUMP_PREFIX_ADDRESS, 16, 4,
			     desc, desc_bytes(desc), 1);

	return 0;
}