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
 void mesh_detach_subs (struct module_qstate*) ; 

int 
fptr_whitelist_modenv_detach_subs(void (*fptr)(
        struct module_qstate* qstate))
{
	if(fptr == &mesh_detach_subs) return 1;
	return 0;
}