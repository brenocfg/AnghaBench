#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct module_env {size_t edns_known_options_num; TYPE_1__* edns_known_options; } ;
struct edns_option {scalar_t__ opt_code; struct edns_option* next; } ;
struct TYPE_2__ {scalar_t__ opt_code; int bypass_cache_stage; } ;

/* Variables and functions */

int
edns_bypass_cache_stage(struct edns_option* list, struct module_env* env)
{
	size_t i;
	for(; list; list=list->next)
		for(i=0; i<env->edns_known_options_num; i++)
			if(env->edns_known_options[i].opt_code == list->opt_code &&
				env->edns_known_options[i].bypass_cache_stage == 1)
					return 1;
	return 0;
}