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
struct icp_qat_uof_sbreak {int dummy; } ;
struct icp_qat_uof_objtable {int /*<<< orphan*/  entry_num; } ;
struct icp_qat_uof_init_regsym {int dummy; } ;
struct icp_qat_uof_image {scalar_t__ sbreak_tab; scalar_t__ init_reg_sym_tab; scalar_t__ reg_tab_offset; } ;
struct icp_qat_uof_encap_obj {scalar_t__ beg_uof; int /*<<< orphan*/  obj_hdr; } ;
struct icp_qat_uof_chunkhdr {scalar_t__ offset; } ;
struct icp_qat_uof_ae_reg {int dummy; } ;
struct icp_qat_uclo_objhandle {TYPE_1__* obj_hdr; struct icp_qat_uof_encap_obj encap_uof_obj; } ;
struct icp_qat_uclo_encapme {int /*<<< orphan*/  page; struct icp_qat_uof_image* img_ptr; struct icp_qat_uof_sbreak* sbreak; int /*<<< orphan*/  sbreak_num; struct icp_qat_uof_init_regsym* init_regsym; int /*<<< orphan*/  init_regsym_num; struct icp_qat_uof_ae_reg* ae_reg; int /*<<< orphan*/  ae_reg_num; } ;
struct icp_qat_uclo_encap_page {int dummy; } ;
struct TYPE_2__ {scalar_t__ file_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICP_QAT_UOF_IMAG ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ qat_uclo_check_image_compat (struct icp_qat_uof_encap_obj*,struct icp_qat_uof_image*) ; 
 struct icp_qat_uof_chunkhdr* qat_uclo_find_chunk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct icp_qat_uof_chunkhdr*) ; 
 int /*<<< orphan*/  qat_uclo_map_image_page (struct icp_qat_uof_encap_obj*,struct icp_qat_uof_image*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qat_uclo_map_uimage(struct icp_qat_uclo_objhandle *obj_handle,
			       struct icp_qat_uclo_encapme *ae_uimage,
			       int max_image)
{
	int i, j;
	struct icp_qat_uof_chunkhdr *chunk_hdr = NULL;
	struct icp_qat_uof_image *image;
	struct icp_qat_uof_objtable *ae_regtab;
	struct icp_qat_uof_objtable *init_reg_sym_tab;
	struct icp_qat_uof_objtable *sbreak_tab;
	struct icp_qat_uof_encap_obj *encap_uof_obj =
					&obj_handle->encap_uof_obj;

	for (j = 0; j < max_image; j++) {
		chunk_hdr = qat_uclo_find_chunk(encap_uof_obj->obj_hdr,
						ICP_QAT_UOF_IMAG, chunk_hdr);
		if (!chunk_hdr)
			break;
		image = (struct icp_qat_uof_image *)(encap_uof_obj->beg_uof +
						     chunk_hdr->offset);
		ae_regtab = (struct icp_qat_uof_objtable *)
			   (image->reg_tab_offset +
			   obj_handle->obj_hdr->file_buff);
		ae_uimage[j].ae_reg_num = ae_regtab->entry_num;
		ae_uimage[j].ae_reg = (struct icp_qat_uof_ae_reg *)
			(((char *)ae_regtab) +
			sizeof(struct icp_qat_uof_objtable));
		init_reg_sym_tab = (struct icp_qat_uof_objtable *)
				   (image->init_reg_sym_tab +
				   obj_handle->obj_hdr->file_buff);
		ae_uimage[j].init_regsym_num = init_reg_sym_tab->entry_num;
		ae_uimage[j].init_regsym = (struct icp_qat_uof_init_regsym *)
			(((char *)init_reg_sym_tab) +
			sizeof(struct icp_qat_uof_objtable));
		sbreak_tab = (struct icp_qat_uof_objtable *)
			(image->sbreak_tab + obj_handle->obj_hdr->file_buff);
		ae_uimage[j].sbreak_num = sbreak_tab->entry_num;
		ae_uimage[j].sbreak = (struct icp_qat_uof_sbreak *)
				      (((char *)sbreak_tab) +
				      sizeof(struct icp_qat_uof_objtable));
		ae_uimage[j].img_ptr = image;
		if (qat_uclo_check_image_compat(encap_uof_obj, image))
			goto out_err;
		ae_uimage[j].page =
			kzalloc(sizeof(struct icp_qat_uclo_encap_page),
				GFP_KERNEL);
		if (!ae_uimage[j].page)
			goto out_err;
		qat_uclo_map_image_page(encap_uof_obj, image,
					ae_uimage[j].page);
	}
	return j;
out_err:
	for (i = 0; i < j; i++)
		kfree(ae_uimage[i].page);
	return 0;
}