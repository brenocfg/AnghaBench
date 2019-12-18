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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ dtrace_id_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dtrace_nfscl_accesscache_flush_done_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_accesscache_get_hit_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_accesscache_get_miss_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_accesscache_load_done_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_attrcache_flush_done_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_attrcache_get_hit_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_attrcache_get_miss_probe ; 
 int /*<<< orphan*/ * dtrace_nfscl_attrcache_load_done_probe ; 
 scalar_t__ nfscl_accesscache_flush_done_id ; 
 scalar_t__ nfscl_accesscache_get_hit_id ; 
 scalar_t__ nfscl_accesscache_get_miss_id ; 
 scalar_t__ nfscl_accesscache_load_done_id ; 
 scalar_t__ nfscl_attrcache_flush_done_id ; 
 scalar_t__ nfscl_attrcache_get_hit_id ; 
 scalar_t__ nfscl_attrcache_get_miss_id ; 
 scalar_t__ nfscl_attrcache_load_done_id ; 

__attribute__((used)) static void
dtnfsclient_disable(void *arg, dtrace_id_t id, void *parg)
{
	uint32_t *p = parg;

	if (id == nfscl_accesscache_flush_done_id)
		dtrace_nfscl_accesscache_flush_done_probe = NULL;
	else if (id == nfscl_accesscache_get_hit_id)
		dtrace_nfscl_accesscache_get_hit_probe = NULL;
	else if (id == nfscl_accesscache_get_miss_id)
		dtrace_nfscl_accesscache_get_miss_probe = NULL;
	else if (id == nfscl_accesscache_load_done_id)
		dtrace_nfscl_accesscache_load_done_probe = NULL;
	else if (id == nfscl_attrcache_flush_done_id)
		dtrace_nfscl_attrcache_flush_done_probe = NULL;
	else if (id == nfscl_attrcache_get_hit_id)
		dtrace_nfscl_attrcache_get_hit_probe = NULL;
	else if (id == nfscl_attrcache_get_miss_id)
		dtrace_nfscl_attrcache_get_miss_probe = NULL;
	else if (id == nfscl_attrcache_load_done_id)
		dtrace_nfscl_attrcache_load_done_probe = NULL;
	else
		*p = 0;
}