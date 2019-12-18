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
struct module_env {int /*<<< orphan*/ ** modinfo; } ;
struct dns64_env {int /*<<< orphan*/  ignore_aaaa; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_ignore_aaaa_node ; 
 int /*<<< orphan*/  traverse_postorder (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
dns64_deinit(struct module_env* env, int id)
{
    struct dns64_env* dns64_env;
    if (!env)
        return;
    dns64_env = (struct dns64_env*)env->modinfo[id];
    if(dns64_env) {
	    traverse_postorder(&dns64_env->ignore_aaaa, free_ignore_aaaa_node,
	    	NULL);
    }
    free(env->modinfo[id]);
    env->modinfo[id] = NULL;
}