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
typedef  void* u32 ;
struct hisi_zip_sqe {void* dest_addr_h; void* dest_addr_l; void* source_addr_h; void* source_addr_l; void* dest_avail_out; int /*<<< orphan*/  dw9; void* input_data_length; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HZIP_REQ_TYPE_M ; 
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct hisi_zip_sqe*,int /*<<< orphan*/ ,int) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hisi_zip_fill_sqe(struct hisi_zip_sqe *sqe, u8 req_type,
			      dma_addr_t s_addr, dma_addr_t d_addr, u32 slen,
			      u32 dlen)
{
	memset(sqe, 0, sizeof(struct hisi_zip_sqe));

	sqe->input_data_length = slen;
	sqe->dw9 = FIELD_PREP(HZIP_REQ_TYPE_M, req_type);
	sqe->dest_avail_out = dlen;
	sqe->source_addr_l = lower_32_bits(s_addr);
	sqe->source_addr_h = upper_32_bits(s_addr);
	sqe->dest_addr_l = lower_32_bits(d_addr);
	sqe->dest_addr_h = upper_32_bits(d_addr);
}