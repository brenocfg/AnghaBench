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
struct TYPE_3__ {int pm_type; } ;

/* Variables and functions */
#define  PT_EPT 130 
#define  PT_RVI 129 
#define  PT_X86 128 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  pg_g ; 

__attribute__((used)) static __inline pt_entry_t
pmap_global_bit(pmap_t pmap)
{
	pt_entry_t mask;

	switch (pmap->pm_type) {
	case PT_X86:
		mask = pg_g;
		break;
	case PT_RVI:
	case PT_EPT:
		mask = 0;
		break;
	default:
		panic("pmap_global_bit: invalid pm_type %d", pmap->pm_type);
	}

	return (mask);
}