#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
struct proc {int dummy; } ;
struct TYPE_4__ {int md_flags; } ;
struct TYPE_6__ {TYPE_1__ p_md; } ;
struct TYPE_5__ {scalar_t__ pm_ucr3; } ;

/* Variables and functions */
 scalar_t__ PMAP_NO_CR3 ; 
 int P_MD_KPTI ; 
 TYPE_3__* curproc ; 
 TYPE_2__* vm_map_pmap (int /*<<< orphan*/ ) ; 

bool
cpu_exec_vmspace_reuse(struct proc *p, vm_map_t map)
{

	return (((curproc->p_md.md_flags & P_MD_KPTI) != 0) ==
	    (vm_map_pmap(map)->pm_ucr3 != PMAP_NO_CR3));
}