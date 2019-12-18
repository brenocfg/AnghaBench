#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct TYPE_4__ {scalar_t__ read_final_eot_; scalar_t__ write_final_eot_; } ;
typedef  TYPE_1__ oxnas_dma_device_settings_t ;

/* Variables and functions */
 unsigned long DMA_BYTE_CNT_RD_EOT_MASK ; 
 unsigned long DMA_BYTE_CNT_WR_EOT_MASK ; 

__attribute__((used)) static u32 encode_final_eot(oxnas_dma_device_settings_t* src_settings,
				oxnas_dma_device_settings_t* dst_settings,
				unsigned long length)
{
	// Write the length, with EOT configuration for a final transfer
	unsigned long encoded = length;
	if (dst_settings->write_final_eot_) {
		encoded |= DMA_BYTE_CNT_WR_EOT_MASK;
	} else {
		encoded &= ~DMA_BYTE_CNT_WR_EOT_MASK;
	}
	if (src_settings->read_final_eot_) {
		encoded |= DMA_BYTE_CNT_RD_EOT_MASK;
	} else {
		encoded &= ~DMA_BYTE_CNT_RD_EOT_MASK;
	}
	/*    if((src_settings->transfer_mode_) ||
	 (src_settings->transfer_mode_)) {
	 encoded |= DMA_BYTE_CNT_BURST_MASK;
	 } else {
	 encoded &= ~DMA_BYTE_CNT_BURST_MASK;
	 }*/
	return encoded;
}