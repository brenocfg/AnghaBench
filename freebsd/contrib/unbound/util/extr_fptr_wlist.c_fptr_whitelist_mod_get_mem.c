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
 size_t cachedb_get_mem (struct module_env*,int) ; 
 size_t dns64_get_mem (struct module_env*,int) ; 
 size_t ipsecmod_get_mem (struct module_env*,int) ; 
 size_t iter_get_mem (struct module_env*,int) ; 
 size_t pythonmod_get_mem (struct module_env*,int) ; 
 size_t respip_get_mem (struct module_env*,int) ; 
 size_t subnetmod_get_mem (struct module_env*,int) ; 
 size_t val_get_mem (struct module_env*,int) ; 

int 
fptr_whitelist_mod_get_mem(size_t (*fptr)(struct module_env* env, int id))
{
	if(fptr == &iter_get_mem) return 1;
	else if(fptr == &val_get_mem) return 1;
	else if(fptr == &dns64_get_mem) return 1;
	else if(fptr == &respip_get_mem) return 1;
#ifdef WITH_PYTHONMODULE
	else if(fptr == &pythonmod_get_mem) return 1;
#endif
#ifdef USE_CACHEDB
	else if(fptr == &cachedb_get_mem) return 1;
#endif
#ifdef USE_IPSECMOD
	else if(fptr == &ipsecmod_get_mem) return 1;
#endif
#ifdef CLIENT_SUBNET
	else if(fptr == &subnetmod_get_mem) return 1;
#endif
	return 0;
}