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
struct pcilynx {int dummy; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 scalar_t__ DMA0_CHAN_CTRL ; 
 scalar_t__ DMA0_CURRENT_PCL ; 
 int DMA_CHAN_CTRL_ENABLE ; 
 int DMA_CHAN_CTRL_LINK ; 
 int /*<<< orphan*/  reg_write (struct pcilynx*,scalar_t__,int) ; 

__attribute__((used)) static inline void
run_pcl(struct pcilynx *lynx, dma_addr_t pcl_bus,
			   int dmachan)
{
	reg_write(lynx, DMA0_CURRENT_PCL + dmachan * 0x20, pcl_bus);
	reg_write(lynx, DMA0_CHAN_CTRL + dmachan * 0x20,
		  DMA_CHAN_CTRL_ENABLE | DMA_CHAN_CTRL_LINK);
}