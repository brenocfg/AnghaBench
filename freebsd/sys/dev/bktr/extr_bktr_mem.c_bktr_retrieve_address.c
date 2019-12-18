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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/  buf; int /*<<< orphan*/  vbibuffer; int /*<<< orphan*/  vbidata; int /*<<< orphan*/  odd_dma_prog; int /*<<< orphan*/  dma_prog; } ;

/* Variables and functions */
#define  BKTR_MEM_BUF 132 
#define  BKTR_MEM_DMA_PROG 131 
 int BKTR_MEM_MAX_DEVICES ; 
#define  BKTR_MEM_ODD_DMA_PROG 130 
#define  BKTR_MEM_VBIBUFFER 129 
#define  BKTR_MEM_VBIDATA 128 
 TYPE_1__* memory_list ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

vm_offset_t
bktr_retrieve_address(int unit, int type)
{

	if (unit < 0 || unit >= BKTR_MEM_MAX_DEVICES) {
		printf("bktr_mem: Unit number %d too large for memory type %d\n",
			unit, type);
		return (0);
	}
	switch (type) {
	case BKTR_MEM_DMA_PROG:
		return memory_list[unit].dma_prog;
	case BKTR_MEM_ODD_DMA_PROG:
		return memory_list[unit].odd_dma_prog;
	case BKTR_MEM_VBIDATA:
		return memory_list[unit].vbidata;
	case BKTR_MEM_VBIBUFFER:
		return memory_list[unit].vbibuffer;
	case BKTR_MEM_BUF:
		return memory_list[unit].buf;
	default:
		printf("bktr_mem: Invalid memory type %d for bktr%d",
		       type, unit);
		return (0);
	}
}