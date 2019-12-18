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

/* Variables and functions */
 void mesh_state_delete (struct module_qstate*) ; 

int 
fptr_whitelist_modenv_kill_sub(void (*fptr)(struct module_qstate* newq))
{
	if(fptr == &mesh_state_delete) return 1;
	return 0;
}