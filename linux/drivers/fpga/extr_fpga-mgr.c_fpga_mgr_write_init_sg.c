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
struct sg_table {int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct sg_mapping_iter {scalar_t__ length; char* addr; } ;
struct fpga_manager {TYPE_1__* mops; } ;
struct fpga_image_info {int dummy; } ;
struct TYPE_2__ {scalar_t__ initial_header_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SG_MITER_FROM_SG ; 
 int fpga_mgr_write_init_buf (struct fpga_manager*,struct fpga_image_info*,char*,size_t) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t sg_copy_to_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ sg_miter_next (struct sg_mapping_iter*) ; 
 int /*<<< orphan*/  sg_miter_start (struct sg_mapping_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_miter_stop (struct sg_mapping_iter*) ; 

__attribute__((used)) static int fpga_mgr_write_init_sg(struct fpga_manager *mgr,
				  struct fpga_image_info *info,
				  struct sg_table *sgt)
{
	struct sg_mapping_iter miter;
	size_t len;
	char *buf;
	int ret;

	if (!mgr->mops->initial_header_size)
		return fpga_mgr_write_init_buf(mgr, info, NULL, 0);

	/*
	 * First try to use miter to map the first fragment to access the
	 * header, this is the typical path.
	 */
	sg_miter_start(&miter, sgt->sgl, sgt->nents, SG_MITER_FROM_SG);
	if (sg_miter_next(&miter) &&
	    miter.length >= mgr->mops->initial_header_size) {
		ret = fpga_mgr_write_init_buf(mgr, info, miter.addr,
					      miter.length);
		sg_miter_stop(&miter);
		return ret;
	}
	sg_miter_stop(&miter);

	/* Otherwise copy the fragments into temporary memory. */
	buf = kmalloc(mgr->mops->initial_header_size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	len = sg_copy_to_buffer(sgt->sgl, sgt->nents, buf,
				mgr->mops->initial_header_size);
	ret = fpga_mgr_write_init_buf(mgr, info, buf, len);

	kfree(buf);

	return ret;
}