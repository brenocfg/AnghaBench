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
typedef  int uint32_t ;
struct TYPE_2__ {int id_dfr0; } ;

/* Variables and functions */
 int ID_DFR0_CP_DEBUG_M_MASK ; 
 int ID_DFR0_CP_DEBUG_M_SHIFT ; 
 TYPE_1__ cpuinfo ; 

__attribute__((used)) static __inline uint32_t
dbg_get_debug_model(void)
{
	uint32_t dbg_m;

	dbg_m = ((cpuinfo.id_dfr0 & ID_DFR0_CP_DEBUG_M_MASK) >>
	    ID_DFR0_CP_DEBUG_M_SHIFT);

	return (dbg_m);
}