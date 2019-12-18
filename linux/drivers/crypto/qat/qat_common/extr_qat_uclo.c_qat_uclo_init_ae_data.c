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
struct icp_qat_uclo_page {int /*<<< orphan*/ * region; int /*<<< orphan*/  encap_page; } ;
struct icp_qat_uclo_objhandle {int /*<<< orphan*/  ustore_phy_size; struct icp_qat_uclo_encapme* ae_uimage; struct icp_qat_uclo_aedata* ae_data; } ;
struct icp_qat_uclo_encapme {int /*<<< orphan*/  page; TYPE_1__* img_ptr; } ;
struct icp_qat_uclo_aeslice {int /*<<< orphan*/ * region; struct icp_qat_uclo_page* page; scalar_t__ ctx_mask_assigned; struct icp_qat_uclo_encapme* encap_image; } ;
struct icp_qat_uclo_aedata {size_t slice_num; int /*<<< orphan*/  eff_ustore_size; struct icp_qat_uclo_aeslice* ae_slices; } ;
struct TYPE_2__ {scalar_t__ ctx_assigned; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_uclo_init_ae_data(struct icp_qat_uclo_objhandle *obj_handle,
				 unsigned int ae, unsigned int image_num)
{
	struct icp_qat_uclo_aedata *ae_data;
	struct icp_qat_uclo_encapme *encap_image;
	struct icp_qat_uclo_page *page = NULL;
	struct icp_qat_uclo_aeslice *ae_slice = NULL;

	ae_data = &obj_handle->ae_data[ae];
	encap_image = &obj_handle->ae_uimage[image_num];
	ae_slice = &ae_data->ae_slices[ae_data->slice_num];
	ae_slice->encap_image = encap_image;

	if (encap_image->img_ptr) {
		ae_slice->ctx_mask_assigned =
					encap_image->img_ptr->ctx_assigned;
		ae_data->eff_ustore_size = obj_handle->ustore_phy_size;
	} else {
		ae_slice->ctx_mask_assigned = 0;
	}
	ae_slice->region = kzalloc(sizeof(*ae_slice->region), GFP_KERNEL);
	if (!ae_slice->region)
		return -ENOMEM;
	ae_slice->page = kzalloc(sizeof(*ae_slice->page), GFP_KERNEL);
	if (!ae_slice->page)
		goto out_err;
	page = ae_slice->page;
	page->encap_page = encap_image->page;
	ae_slice->page->region = ae_slice->region;
	ae_data->slice_num++;
	return 0;
out_err:
	kfree(ae_slice->region);
	ae_slice->region = NULL;
	return -ENOMEM;
}