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
typedef  void* vm_offset_t ;
struct TYPE_2__ {int addresses_stored; void* buf; void* vbibuffer; void* vbidata; void* odd_dma_prog; void* dma_prog; } ;

/* Variables and functions */
#define  BKTR_MEM_BUF 132 
#define  BKTR_MEM_DMA_PROG 131 
 int BKTR_MEM_MAX_DEVICES ; 
#define  BKTR_MEM_ODD_DMA_PROG 130 
#define  BKTR_MEM_VBIBUFFER 129 
#define  BKTR_MEM_VBIDATA 128 
 TYPE_1__* memory_list ; 
 int /*<<< orphan*/  printf (char*,int,int,void*) ; 

void
bktr_store_address(int unit, int type, vm_offset_t addr)
{

	if (unit < 0 || unit >= BKTR_MEM_MAX_DEVICES) {
		printf("bktr_mem: Unit number %d invalid for memory type %d, address %p\n",
		       unit, type, (void *) addr);
		return;
	}

	switch (type) {
	case BKTR_MEM_DMA_PROG:
		memory_list[unit].dma_prog = addr;
		memory_list[unit].addresses_stored = 1;
		break;
	case BKTR_MEM_ODD_DMA_PROG:
		memory_list[unit].odd_dma_prog = addr;
		memory_list[unit].addresses_stored = 1;
		break;
	case BKTR_MEM_VBIDATA:
		memory_list[unit].vbidata = addr;
		memory_list[unit].addresses_stored = 1;
		break;
	case BKTR_MEM_VBIBUFFER:
		memory_list[unit].vbibuffer = addr;
		memory_list[unit].addresses_stored = 1;
		break;
	case BKTR_MEM_BUF:
		memory_list[unit].buf = addr;
		memory_list[unit].addresses_stored = 1;
		break;
	default:
		printf("bktr_mem: Invalid memory type %d for bktr%d, address %p\n",
			type, unit, (void *)addr);
		break;
	}
}