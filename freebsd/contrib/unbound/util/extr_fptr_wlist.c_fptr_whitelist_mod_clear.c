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
 void cachedb_clear (struct module_qstate*,int) ; 
 void dns64_clear (struct module_qstate*,int) ; 
 void ipsecmod_clear (struct module_qstate*,int) ; 
 void iter_clear (struct module_qstate*,int) ; 
 void pythonmod_clear (struct module_qstate*,int) ; 
 void respip_clear (struct module_qstate*,int) ; 
 void subnetmod_clear (struct module_qstate*,int) ; 
 void val_clear (struct module_qstate*,int) ; 

int 
fptr_whitelist_mod_clear(void (*fptr)(struct module_qstate* qstate,
        int id))
{
	if(fptr == &iter_clear) return 1;
	else if(fptr == &val_clear) return 1;
	else if(fptr == &dns64_clear) return 1;
	else if(fptr == &respip_clear) return 1;
#ifdef WITH_PYTHONMODULE
	else if(fptr == &pythonmod_clear) return 1;
#endif
#ifdef USE_CACHEDB
	else if(fptr == &cachedb_clear) return 1;
#endif
#ifdef USE_IPSECMOD
	else if(fptr == &ipsecmod_clear) return 1;
#endif
#ifdef CLIENT_SUBNET
	else if(fptr == &subnetmod_clear) return 1;
#endif
	return 0;
}