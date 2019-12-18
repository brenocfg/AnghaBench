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
typedef  struct module_func_block* (* fbgetfunctype ) () ;

/* Variables and functions */
 int /*<<< orphan*/  cachedb_get_funcblock ; 
 int /*<<< orphan*/  dns64_get_funcblock ; 
 int /*<<< orphan*/  ipsecmod_get_funcblock ; 
 int /*<<< orphan*/  iter_get_funcblock ; 
 int /*<<< orphan*/  pythonmod_get_funcblock ; 
 int /*<<< orphan*/  respip_get_funcblock ; 
 int /*<<< orphan*/  subnetmod_get_funcblock ; 
 int /*<<< orphan*/  val_get_funcblock ; 

__attribute__((used)) static fbgetfunctype*
module_funcs_avail(void)
{
        static struct module_func_block* (*fb[])(void) = {
		&dns64_get_funcblock,
#ifdef WITH_PYTHONMODULE
		&pythonmod_get_funcblock,
#endif
#ifdef USE_CACHEDB
		&cachedb_get_funcblock,
#endif
#ifdef USE_IPSECMOD
		&ipsecmod_get_funcblock,
#endif
#ifdef CLIENT_SUBNET
		&subnetmod_get_funcblock,
#endif
		&respip_get_funcblock,
		&val_get_funcblock,
		&iter_get_funcblock,
		NULL};
	return fb;
}