#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_8__ {unsigned long address_; int /*<<< orphan*/  address_mode_; } ;
typedef  TYPE_1__ oxnas_dma_device_settings_t ;
struct TYPE_9__ {unsigned long address_; } ;

/* Variables and functions */
 scalar_t__ DMA_BASE_DST_ADR ; 
 scalar_t__ DMA_BASE_SRC_ADR ; 
 scalar_t__ DMA_BYTE_CNT ; 
 scalar_t__ DMA_CTRL_STATUS ; 
 int /*<<< orphan*/  OXNAS_DMA_MODE_INC ; 
 scalar_t__ SATA_DMA_REGS_BASE ; 
 int /*<<< orphan*/  dma_start () ; 
 unsigned long encode_control_status (TYPE_1__*,TYPE_2__*) ; 
 unsigned long encode_final_eot (TYPE_1__*,TYPE_2__*,int) ; 
 TYPE_1__ oxnas_ram_dma_settings ; 
 TYPE_2__ oxnas_sata_dma_settings ; 
 int /*<<< orphan*/  writel (unsigned long,scalar_t__) ; 

__attribute__((used)) static void dma_start_write(const ulong* buffer, int num_bytes)
{
	// Assemble complete memory settings
	oxnas_dma_device_settings_t mem_settings = oxnas_ram_dma_settings;
	mem_settings.address_ = (unsigned long) buffer;
	mem_settings.address_mode_ = OXNAS_DMA_MODE_INC;

	writel(encode_control_status(&mem_settings, &oxnas_sata_dma_settings),
		SATA_DMA_REGS_BASE + DMA_CTRL_STATUS);
	writel(mem_settings.address_, SATA_DMA_REGS_BASE + DMA_BASE_SRC_ADR);
	writel(oxnas_sata_dma_settings.address_,
		SATA_DMA_REGS_BASE + DMA_BASE_DST_ADR);
	writel(encode_final_eot(&mem_settings, &oxnas_sata_dma_settings,
				num_bytes),
		SATA_DMA_REGS_BASE + DMA_BYTE_CNT);

	dma_start();
}