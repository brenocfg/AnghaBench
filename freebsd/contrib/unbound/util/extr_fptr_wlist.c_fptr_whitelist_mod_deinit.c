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
 void cachedb_deinit (struct module_env*,int) ; 
 void dns64_deinit (struct module_env*,int) ; 
 void ipsecmod_deinit (struct module_env*,int) ; 
 void iter_deinit (struct module_env*,int) ; 
 void pythonmod_deinit (struct module_env*,int) ; 
 void respip_deinit (struct module_env*,int) ; 
 void subnetmod_deinit (struct module_env*,int) ; 
 void val_deinit (struct module_env*,int) ; 

int 
fptr_whitelist_mod_deinit(void (*fptr)(struct module_env* env, int id))
{
	if(fptr == &iter_deinit) return 1;
	else if(fptr == &val_deinit) return 1;
	else if(fptr == &dns64_deinit) return 1;
	else if(fptr == &respip_deinit) return 1;
#ifdef WITH_PYTHONMODULE
	else if(fptr == &pythonmod_deinit) return 1;
#endif
#ifdef USE_CACHEDB
	else if(fptr == &cachedb_deinit) return 1;
#endif
#ifdef USE_IPSECMOD
	else if(fptr == &ipsecmod_deinit) return 1;
#endif
#ifdef CLIENT_SUBNET
	else if(fptr == &subnetmod_deinit) return 1;
#endif
	return 0;
}