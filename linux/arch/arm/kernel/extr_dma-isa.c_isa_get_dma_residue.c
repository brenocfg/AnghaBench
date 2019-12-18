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
typedef  int /*<<< orphan*/  dma_t ;

/* Variables and functions */
 size_t ISA_DMA_COUNT ; 
 int inb (unsigned int) ; 
 unsigned int** isa_dma_port ; 

__attribute__((used)) static int isa_get_dma_residue(unsigned int chan, dma_t *dma)
{
	unsigned int io_port = isa_dma_port[chan][ISA_DMA_COUNT];
	int count;

	count = 1 + inb(io_port);
	count |= inb(io_port) << 8;

	return chan < 4 ? count : (count << 1);
}