#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  h2o_req_t ;
struct TYPE_9__ {size_t size; TYPE_5__* entries; } ;
struct TYPE_8__ {size_t size; TYPE_1__* entries; } ;
struct TYPE_10__ {TYPE_3__ sets; TYPE_2__ unsets; struct TYPE_10__* parent; } ;
typedef  TYPE_4__ h2o_envconf_t ;
struct TYPE_11__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_5__* h2o_req_getenv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  h2o_req_unsetenv (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apply_env(h2o_req_t *req, h2o_envconf_t *env)
{
    size_t i;

    if (env->parent != NULL)
        apply_env(req, env->parent);
    for (i = 0; i != env->unsets.size; ++i)
        h2o_req_unsetenv(req, env->unsets.entries[i].base, env->unsets.entries[i].len);
    for (i = 0; i != env->sets.size; i += 2)
        *h2o_req_getenv(req, env->sets.entries[i].base, env->sets.entries[i].len, 1) = env->sets.entries[i + 1];
}