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
typedef  int vm_offset_t ;
typedef  int uint64_t ;
struct TYPE_2__ {int td_pcb; } ;

/* Variables and functions */
 scalar_t__ PCPU_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCPU_SET (int,int) ; 
 int PC_PTI_STACK_SZ ; 
 int curpcb ; 
 int pti_rsp0 ; 
 int /*<<< orphan*/  pti_stack ; 
 TYPE_1__ thread0 ; 

void
amd64_bsp_pcpu_init2(uint64_t rsp0)
{

	PCPU_SET(rsp0, rsp0);
	PCPU_SET(pti_rsp0, ((vm_offset_t)PCPU_PTR(pti_stack) +
	    PC_PTI_STACK_SZ * sizeof(uint64_t)) & ~0xful);
	PCPU_SET(curpcb, thread0.td_pcb);
}