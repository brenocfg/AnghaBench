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
struct s5p_hash_reqctx {unsigned int bufcnt; int error; int sg_len; TYPE_1__* dd; int /*<<< orphan*/  skip; int /*<<< orphan*/  sgl; int /*<<< orphan*/  sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  hash_flags; int /*<<< orphan*/  xmit_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  HASH_FLAGS_SGS_COPIED ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned int get_order (unsigned int) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scatterwalk_map_and_copy (void*,struct scatterlist*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sg_init_table (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sg_set_buf (int /*<<< orphan*/ ,void*,unsigned int) ; 

__attribute__((used)) static int s5p_hash_copy_sgs(struct s5p_hash_reqctx *ctx,
			     struct scatterlist *sg, unsigned int new_len)
{
	unsigned int pages, len;
	void *buf;

	len = new_len + ctx->bufcnt;
	pages = get_order(len);

	buf = (void *)__get_free_pages(GFP_ATOMIC, pages);
	if (!buf) {
		dev_err(ctx->dd->dev, "alloc pages for unaligned case.\n");
		ctx->error = true;
		return -ENOMEM;
	}

	if (ctx->bufcnt)
		memcpy(buf, ctx->dd->xmit_buf, ctx->bufcnt);

	scatterwalk_map_and_copy(buf + ctx->bufcnt, sg, ctx->skip,
				 new_len, 0);
	sg_init_table(ctx->sgl, 1);
	sg_set_buf(ctx->sgl, buf, len);
	ctx->sg = ctx->sgl;
	ctx->sg_len = 1;
	ctx->bufcnt = 0;
	ctx->skip = 0;
	set_bit(HASH_FLAGS_SGS_COPIED, &ctx->dd->hash_flags);

	return 0;
}