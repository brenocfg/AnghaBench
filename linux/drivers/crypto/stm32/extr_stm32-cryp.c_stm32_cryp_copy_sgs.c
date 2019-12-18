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
struct stm32_cryp {int sgs_copied; int in_sg_len; int out_sg_len; int /*<<< orphan*/  out_sgl; int /*<<< orphan*/ * out_sg; int /*<<< orphan*/ * out_sg_save; int /*<<< orphan*/  in_sgl; int /*<<< orphan*/ * in_sg; int /*<<< orphan*/  total_in; int /*<<< orphan*/  dev; int /*<<< orphan*/  hw_blocksize; int /*<<< orphan*/  total_out; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EFAULT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_order (int) ; 
 int /*<<< orphan*/  sg_copy_buf (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  stm32_cryp_check_io_aligned (struct stm32_cryp*) ; 

__attribute__((used)) static int stm32_cryp_copy_sgs(struct stm32_cryp *cryp)
{
	void *buf_in, *buf_out;
	int pages, total_in, total_out;

	if (!stm32_cryp_check_io_aligned(cryp)) {
		cryp->sgs_copied = 0;
		return 0;
	}

	total_in = ALIGN(cryp->total_in, cryp->hw_blocksize);
	pages = total_in ? get_order(total_in) : 1;
	buf_in = (void *)__get_free_pages(GFP_ATOMIC, pages);

	total_out = ALIGN(cryp->total_out, cryp->hw_blocksize);
	pages = total_out ? get_order(total_out) : 1;
	buf_out = (void *)__get_free_pages(GFP_ATOMIC, pages);

	if (!buf_in || !buf_out) {
		dev_err(cryp->dev, "Can't allocate pages when unaligned\n");
		cryp->sgs_copied = 0;
		return -EFAULT;
	}

	sg_copy_buf(buf_in, cryp->in_sg, 0, cryp->total_in, 0);

	sg_init_one(&cryp->in_sgl, buf_in, total_in);
	cryp->in_sg = &cryp->in_sgl;
	cryp->in_sg_len = 1;

	sg_init_one(&cryp->out_sgl, buf_out, total_out);
	cryp->out_sg_save = cryp->out_sg;
	cryp->out_sg = &cryp->out_sgl;
	cryp->out_sg_len = 1;

	cryp->sgs_copied = 1;

	return 0;
}