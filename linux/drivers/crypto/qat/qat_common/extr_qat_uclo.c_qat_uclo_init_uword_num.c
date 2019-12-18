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
struct icp_qat_uclo_objhandle {int uimage_num; struct icp_qat_uclo_encapme* ae_uimage; } ;
struct icp_qat_uclo_encapme {TYPE_1__* page; scalar_t__ uwords_num; } ;
struct icp_qat_fw_loader_handle {struct icp_qat_uclo_objhandle* obj_handle; } ;
struct TYPE_2__ {scalar_t__ micro_words_num; scalar_t__ beg_addr_p; } ;

/* Variables and functions */

__attribute__((used)) static void qat_uclo_init_uword_num(struct icp_qat_fw_loader_handle *handle)
{
	struct icp_qat_uclo_objhandle *obj_handle = handle->obj_handle;
	struct icp_qat_uclo_encapme *image;
	int a;

	for (a = 0; a < obj_handle->uimage_num; a++) {
		image = &obj_handle->ae_uimage[a];
		image->uwords_num = image->page->beg_addr_p +
					image->page->micro_words_num;
	}
}