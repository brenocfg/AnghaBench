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
typedef  scalar_t__ uint16_t ;
struct module_env {size_t edns_known_options_num; struct edns_known_option* edns_known_options; } ;
struct edns_known_option {scalar_t__ opt_code; } ;

/* Variables and functions */

struct edns_known_option*
edns_option_is_known(uint16_t opt_code, struct module_env* env)
{
	size_t i;
	for(i=0; i<env->edns_known_options_num; i++)
		if(env->edns_known_options[i].opt_code == opt_code)
			return env->edns_known_options + i;
	return NULL;
}