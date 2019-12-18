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
struct module_env {scalar_t__* modinfo; } ;
struct dns64_env {int dummy; } ;

/* Variables and functions */

size_t
dns64_get_mem(struct module_env* env, int id)
{
    struct dns64_env* dns64_env = (struct dns64_env*)env->modinfo[id];
    if (!dns64_env)
        return 0;
    return sizeof(*dns64_env);
}