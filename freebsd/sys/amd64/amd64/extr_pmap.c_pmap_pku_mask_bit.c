#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {scalar_t__ pm_type; } ;

/* Variables and functions */
 scalar_t__ PT_X86 ; 
 int /*<<< orphan*/  X86_PG_PKU_MASK ; 

__attribute__((used)) static __inline pt_entry_t
pmap_pku_mask_bit(pmap_t pmap)
{

	return (pmap->pm_type == PT_X86 ? X86_PG_PKU_MASK : 0);
}