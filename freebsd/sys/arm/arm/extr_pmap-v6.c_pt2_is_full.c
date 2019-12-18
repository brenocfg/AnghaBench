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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int boolean_t ;
struct TYPE_4__ {scalar_t__* pt2_wirecount; } ;
struct TYPE_5__ {TYPE_1__ md; } ;

/* Variables and functions */
 scalar_t__ NPTE2_IN_PT2 ; 
 size_t PT2PG_MASK ; 
 size_t pte1_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline boolean_t
pt2_is_full(vm_page_t m, vm_offset_t va)
{

	return (m->md.pt2_wirecount[pte1_index(va) & PT2PG_MASK] ==
	    NPTE2_IN_PT2);
}