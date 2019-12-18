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
struct module_env {struct edns_known_option* edns_known_options; scalar_t__ edns_known_options_num; } ;
struct edns_known_option {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_KNOWN_EDNS_OPTS ; 
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 

int
edns_known_options_init(struct module_env* env)
{
	env->edns_known_options_num = 0;
	env->edns_known_options = (struct edns_known_option*)calloc(
		MAX_KNOWN_EDNS_OPTS, sizeof(struct edns_known_option));
	if(!env->edns_known_options) return 0;
	return 1;
}