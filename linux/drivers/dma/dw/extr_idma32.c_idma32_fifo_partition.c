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
typedef  int u64 ;
struct dw_dma {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIFO_PARTITION0 ; 
 int /*<<< orphan*/  FIFO_PARTITION1 ; 
 int IDMA32C_FP_PSIZE_CH0 (int) ; 
 int IDMA32C_FP_PSIZE_CH1 (int) ; 
 int IDMA32C_FP_UPDATE ; 
 int /*<<< orphan*/  idma32_writeq (struct dw_dma*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void idma32_fifo_partition(struct dw_dma *dw)
{
	u64 value = IDMA32C_FP_PSIZE_CH0(64) | IDMA32C_FP_PSIZE_CH1(64) |
		    IDMA32C_FP_UPDATE;
	u64 fifo_partition = 0;

	/* Fill FIFO_PARTITION low bits (Channels 0..1, 4..5) */
	fifo_partition |= value << 0;

	/* Fill FIFO_PARTITION high bits (Channels 2..3, 6..7) */
	fifo_partition |= value << 32;

	/* Program FIFO Partition registers - 64 bytes per channel */
	idma32_writeq(dw, FIFO_PARTITION1, fifo_partition);
	idma32_writeq(dw, FIFO_PARTITION0, fifo_partition);
}