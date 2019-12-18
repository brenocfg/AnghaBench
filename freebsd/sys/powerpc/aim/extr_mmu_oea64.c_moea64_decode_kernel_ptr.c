#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_8__ {TYPE_3__* td_pcb; } ;
struct TYPE_5__ {int usr_segm; } ;
struct TYPE_6__ {TYPE_1__ aim; } ;
struct TYPE_7__ {TYPE_2__ pcb_cpu; } ;

/* Variables and functions */
 int ADDR_PIDX ; 
 int ADDR_POFF ; 
 int ADDR_SR_SHFT ; 
 int USER_ADDR ; 
 TYPE_4__* curthread ; 

__attribute__((used)) static int
moea64_decode_kernel_ptr(mmu_t mmu, vm_offset_t addr, int *is_user,
    vm_offset_t *decoded_addr)
{
	vm_offset_t user_sr;

	if ((addr >> ADDR_SR_SHFT) == (USER_ADDR >> ADDR_SR_SHFT)) {
		user_sr = curthread->td_pcb->pcb_cpu.aim.usr_segm;
		addr &= ADDR_PIDX | ADDR_POFF;
		addr |= user_sr << ADDR_SR_SHFT;
		*decoded_addr = addr;
		*is_user = 1;
	} else {
		*decoded_addr = addr;
		*is_user = 0;
	}

	return (0);
}