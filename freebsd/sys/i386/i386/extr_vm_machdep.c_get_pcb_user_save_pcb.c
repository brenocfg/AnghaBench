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
typedef  scalar_t__ vm_offset_t ;
typedef  union savefpu {int dummy; } savefpu ;
struct pcb {int dummy; } ;

/* Variables and functions */

union savefpu *
get_pcb_user_save_pcb(struct pcb *pcb)
{
	vm_offset_t p;

	p = (vm_offset_t)(pcb + 1);
	return ((union savefpu *)p);
}