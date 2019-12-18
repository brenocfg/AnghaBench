#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
struct TYPE_4__ {int mdpg_attrs; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
moea_attr_save(vm_page_t m, int ptebit)
{

	rw_assert(&pvh_global_lock, RA_WLOCKED);
	m->md.mdpg_attrs |= ptebit;
}