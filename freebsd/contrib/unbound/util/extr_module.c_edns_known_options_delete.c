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
struct module_env {scalar_t__ edns_known_options_num; int /*<<< orphan*/ * edns_known_options; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
edns_known_options_delete(struct module_env* env)
{
	free(env->edns_known_options);
	env->edns_known_options = NULL;
	env->edns_known_options_num = 0;
}