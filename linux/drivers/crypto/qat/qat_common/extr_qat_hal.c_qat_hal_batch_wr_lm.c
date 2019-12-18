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
typedef  int uint64_t ;
struct icp_qat_uof_batch_init {int size; unsigned char ae; unsigned int addr; unsigned int* value; struct icp_qat_uof_batch_init* next; } ;
struct icp_qat_fw_loader_handle {TYPE_1__* hal_handle; } ;
struct TYPE_2__ {unsigned int max_ustore; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qat_hal_concat_micro_code (int*,int,unsigned int,unsigned int,unsigned int*) ; 
 int qat_hal_exec_micro_init_lm (struct icp_qat_fw_loader_handle*,unsigned char,int /*<<< orphan*/ ,int*,int*,int) ; 

int qat_hal_batch_wr_lm(struct icp_qat_fw_loader_handle *handle,
			unsigned char ae,
			struct icp_qat_uof_batch_init *lm_init_header)
{
	struct icp_qat_uof_batch_init *plm_init;
	uint64_t *micro_inst_arry;
	int micro_inst_num;
	int alloc_inst_size;
	int first_exec = 1;
	int stat = 0;

	plm_init = lm_init_header->next;
	alloc_inst_size = lm_init_header->size;
	if ((unsigned int)alloc_inst_size > handle->hal_handle->max_ustore)
		alloc_inst_size = handle->hal_handle->max_ustore;
	micro_inst_arry = kmalloc_array(alloc_inst_size, sizeof(uint64_t),
					GFP_KERNEL);
	if (!micro_inst_arry)
		return -ENOMEM;
	micro_inst_num = 0;
	while (plm_init) {
		unsigned int addr, *value, size;

		ae = plm_init->ae;
		addr = plm_init->addr;
		value = plm_init->value;
		size = plm_init->size;
		micro_inst_num += qat_hal_concat_micro_code(micro_inst_arry,
							    micro_inst_num,
							    size, addr, value);
		plm_init = plm_init->next;
	}
	/* exec micro codes */
	if (micro_inst_arry && (micro_inst_num > 0)) {
		micro_inst_arry[micro_inst_num++] = 0x0E000010000ull;
		stat = qat_hal_exec_micro_init_lm(handle, ae, 0, &first_exec,
						  micro_inst_arry,
						  micro_inst_num);
	}
	kfree(micro_inst_arry);
	return stat;
}