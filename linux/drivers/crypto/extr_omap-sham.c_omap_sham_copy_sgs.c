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
struct scatterlist {int dummy; } ;
struct omap_sham_reqctx {int bufcnt; int sg_len; int /*<<< orphan*/  offset; TYPE_1__* dd; int /*<<< orphan*/  sgl; int /*<<< orphan*/  sg; scalar_t__ total; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  xmit_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FLAGS_SGS_COPIED ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int get_order (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (void*,struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int omap_sham_copy_sgs(struct omap_sham_reqctx *ctx,
			      struct scatterlist *sg, int bs, int new_len)
{
	int pages;
	void *buf;
	int len;

	len = new_len + ctx->bufcnt;

	pages = get_order(ctx->total);

	buf = (void *)__get_free_pages(GFP_ATOMIC, pages);
	if (!buf) {
		pr_err("Couldn't allocate pages for unaligned cases.\n");
		return -ENOMEM;
	}

	if (ctx->bufcnt)
		memcpy(buf, ctx->dd->xmit_buf, ctx->bufcnt);

	scatterwalk_map_and_copy(buf + ctx->bufcnt, sg, ctx->offset,
				 ctx->total - ctx->bufcnt, 0);
	sg_init_table(ctx->sgl, 1);
	sg_set_buf(ctx->sgl, buf, len);
	ctx->sg = ctx->sgl;
	set_bit(FLAGS_SGS_COPIED, &ctx->dd->flags);
	ctx->sg_len = 1;
	ctx->bufcnt = 0;
	ctx->offset = 0;

	return 0;
}