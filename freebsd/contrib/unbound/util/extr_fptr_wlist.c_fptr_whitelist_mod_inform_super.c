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
 void cachedb_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void dns64_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void ipsecmod_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void iter_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void pythonmod_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void respip_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void subnetmod_inform_super (struct module_qstate*,int,struct module_qstate*) ; 
 void val_inform_super (struct module_qstate*,int,struct module_qstate*) ; 

int 
fptr_whitelist_mod_inform_super(void (*fptr)(
        struct module_qstate* qstate, int id, struct module_qstate* super))
{
	if(fptr == &iter_inform_super) return 1;
	else if(fptr == &val_inform_super) return 1;
	else if(fptr == &dns64_inform_super) return 1;
	else if(fptr == &respip_inform_super) return 1;
#ifdef WITH_PYTHONMODULE
	else if(fptr == &pythonmod_inform_super) return 1;
#endif
#ifdef USE_CACHEDB
	else if(fptr == &cachedb_inform_super) return 1;
#endif
#ifdef USE_IPSECMOD
	else if(fptr == &ipsecmod_inform_super) return 1;
#endif
#ifdef CLIENT_SUBNET
	else if(fptr == &subnetmod_inform_super) return 1;
#endif
	return 0;
}