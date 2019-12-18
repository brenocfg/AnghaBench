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
struct TYPE_3__ {scalar_t__ asz; } ;
struct TYPE_4__ {TYPE_1__ s; } ;
struct pt_ild {TYPE_2__ u; } ;
typedef  enum pt_exec_mode { ____Placeholder_pt_exec_mode } pt_exec_mode ;

/* Variables and functions */
 scalar_t__ mode_32b (struct pt_ild const*) ; 
 int ptem_16bit ; 
 int ptem_32bit ; 

__attribute__((used)) static inline enum pt_exec_mode
pti_get_nominal_easz_non64(const struct pt_ild *ild)
{
	if (mode_32b(ild)) {
		if (ild->u.s.asz)
			return ptem_16bit;
		return ptem_32bit;
	}
	if (ild->u.s.asz)
		return ptem_32bit;
	return ptem_16bit;
}