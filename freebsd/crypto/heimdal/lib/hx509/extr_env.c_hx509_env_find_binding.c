#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_5__ {TYPE_2__* list; } ;
struct TYPE_6__ {scalar_t__ type; struct TYPE_6__* next; TYPE_1__ u; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ env_list ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

hx509_env
hx509_env_find_binding(hx509_context context,
		       hx509_env env,
		       const char *key)
{
    while(env) {
	if (strcmp(key, env->name) == 0 && env->type == env_list)
	    return env->u.list;
	env = env->next;
    }
    return NULL;
}