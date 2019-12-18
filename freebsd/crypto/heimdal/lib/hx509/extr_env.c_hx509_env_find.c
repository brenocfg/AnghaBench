#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* hx509_env ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_4__ {char const* string; } ;
struct TYPE_5__ {scalar_t__ type; struct TYPE_5__* next; TYPE_1__ u; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ env_string ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

const char *
hx509_env_find(hx509_context context, hx509_env env, const char *key)
{
    while(env) {
	if (strcmp(key, env->name) == 0 && env->type == env_string)
	    return env->u.string;
	env = env->next;
    }
    return NULL;
}