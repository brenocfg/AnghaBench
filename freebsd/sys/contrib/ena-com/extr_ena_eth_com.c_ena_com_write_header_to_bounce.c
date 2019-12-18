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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct ena_com_llq_pkt_ctrl {int /*<<< orphan*/ * curr_bounce_buf; } ;
struct ena_com_llq_info {scalar_t__ descs_num_before_header; scalar_t__ desc_list_entry_size; } ;
struct ena_com_io_sq {scalar_t__ mem_queue_type; scalar_t__ desc_entry_size; struct ena_com_llq_info llq_info; struct ena_com_llq_pkt_ctrl llq_buf_ctrl; } ;

/* Variables and functions */
 scalar_t__ ENA_ADMIN_PLACEMENT_POLICY_HOST ; 
 int ENA_COM_FAULT ; 
 int /*<<< orphan*/  ena_trc_err (char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ena_com_write_header_to_bounce(struct ena_com_io_sq *io_sq,
						 u8 *header_src,
						 u16 header_len)
{
	struct ena_com_llq_pkt_ctrl *pkt_ctrl = &io_sq->llq_buf_ctrl;
	struct ena_com_llq_info *llq_info = &io_sq->llq_info;
	u8 *bounce_buffer = pkt_ctrl->curr_bounce_buf;
	u16 header_offset;

	if (unlikely(io_sq->mem_queue_type == ENA_ADMIN_PLACEMENT_POLICY_HOST))
		return 0;

	header_offset =
		llq_info->descs_num_before_header * io_sq->desc_entry_size;

	if (unlikely((header_offset + header_len) >  llq_info->desc_list_entry_size)) {
		ena_trc_err("trying to write header larger than llq entry can accommodate\n");
		return ENA_COM_FAULT;
	}

	if (unlikely(!bounce_buffer)) {
		ena_trc_err("bounce buffer is NULL\n");
		return ENA_COM_FAULT;
	}

	memcpy(bounce_buffer + header_offset, header_src, header_len);

	return 0;
}