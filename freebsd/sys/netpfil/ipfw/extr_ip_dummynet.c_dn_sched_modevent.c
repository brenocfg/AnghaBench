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
struct dn_alg {int dummy; } ;
typedef  int /*<<< orphan*/  module_t ;

/* Variables and functions */
 int EINVAL ; 
 int MOD_LOAD ; 
 int MOD_UNLOAD ; 
 int load_dn_sched (struct dn_alg*) ; 
 int unload_dn_sched (struct dn_alg*) ; 

int
dn_sched_modevent(module_t mod, int cmd, void *arg)
{
	struct dn_alg *sch = arg;

	if (cmd == MOD_LOAD)
		return load_dn_sched(sch);
	else if (cmd == MOD_UNLOAD)
		return unload_dn_sched(sch);
	else
		return EINVAL;
}