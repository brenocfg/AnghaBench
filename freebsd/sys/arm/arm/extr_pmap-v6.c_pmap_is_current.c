#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pmap_t ;
struct TYPE_4__ {TYPE_1__* td_proc; } ;
struct TYPE_3__ {int /*<<< orphan*/  p_vmspace; } ;

/* Variables and functions */
 TYPE_2__* curthread ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ vmspace_pmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
pmap_is_current(pmap_t pmap)
{

	return (pmap == kernel_pmap ||
		(pmap == vmspace_pmap(curthread->td_proc->p_vmspace)));
}