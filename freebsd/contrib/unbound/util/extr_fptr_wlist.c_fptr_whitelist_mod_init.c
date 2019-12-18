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
 int cachedb_init (struct module_env*,int) ; 
 int dns64_init (struct module_env*,int) ; 
 int ipsecmod_init (struct module_env*,int) ; 
 int iter_init (struct module_env*,int) ; 
 int pythonmod_init (struct module_env*,int) ; 
 int respip_init (struct module_env*,int) ; 
 int subnetmod_init (struct module_env*,int) ; 
 int val_init (struct module_env*,int) ; 

int 
fptr_whitelist_mod_init(int (*fptr)(struct module_env* env, int id))
{
	if(fptr == &iter_init) return 1;
	else if(fptr == &val_init) return 1;
	else if(fptr == &dns64_init) return 1;
	else if(fptr == &respip_init) return 1;
#ifdef WITH_PYTHONMODULE
	else if(fptr == &pythonmod_init) return 1;
#endif
#ifdef USE_CACHEDB
	else if(fptr == &cachedb_init) return 1;
#endif
#ifdef USE_IPSECMOD
	else if(fptr == &ipsecmod_init) return 1;
#endif
#ifdef CLIENT_SUBNET
	else if(fptr == &subnetmod_init) return 1;
#endif
	return 0;
}