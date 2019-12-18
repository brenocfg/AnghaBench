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
struct module_env {int /*<<< orphan*/  cfg; void** modinfo; } ;
struct dns64_env {int /*<<< orphan*/  ignore_aaaa; } ;

/* Variables and functions */
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  dns64_apply_cfg (struct dns64_env*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  name_tree_init (int /*<<< orphan*/ *) ; 

int
dns64_init(struct module_env* env, int id)
{
    struct dns64_env* dns64_env =
        (struct dns64_env*)calloc(1, sizeof(struct dns64_env));
    if (!dns64_env) {
        log_err("malloc failure");
        return 0;
    }
    env->modinfo[id] = (void*)dns64_env;
    name_tree_init(&dns64_env->ignore_aaaa);
    if (!dns64_apply_cfg(dns64_env, env->cfg)) {
        log_err("dns64: could not apply configuration settings.");
        return 0;
    }
    return 1;
}