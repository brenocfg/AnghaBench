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
struct module_qstate {struct mesh_state* mesh_info; } ;
struct mesh_state {int dummy; } ;

/* Variables and functions */
 size_t MESH_MAX_SUBSUB ; 
 scalar_t__ find_in_subsub (struct mesh_state*,struct mesh_state*,size_t*) ; 

__attribute__((used)) static int 
mesh_detect_cycle_found(struct module_qstate* qstate, struct mesh_state* dep_m)
{
	struct mesh_state* cyc_m = qstate->mesh_info;
	size_t counter = 0;
	if(!dep_m)
		return 0;
	if(dep_m == cyc_m || find_in_subsub(dep_m, cyc_m, &counter)) {
		if(counter > MESH_MAX_SUBSUB)
			return 2;
		return 1;
	}
	return 0;
}