#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; TYPE_4__* entries; } ;
struct TYPE_5__ {size_t size; TYPE_4__* entries; } ;
struct TYPE_7__ {TYPE_2__ sets; TYPE_1__ unsets; int /*<<< orphan*/ * parent; } ;
typedef  TYPE_3__ h2o_envconf_t ;
struct TYPE_8__ {int /*<<< orphan*/ * base; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_dispose_envconf(void *_envconf)
{
    h2o_envconf_t *envconf = _envconf;
    size_t i;

    if (envconf->parent != NULL)
        h2o_mem_release_shared(envconf->parent);

    for (i = 0; i != envconf->unsets.size; ++i)
        h2o_mem_release_shared(envconf->unsets.entries[i].base);
    free(envconf->unsets.entries);
    for (i = 0; i != envconf->sets.size; ++i)
        h2o_mem_release_shared(envconf->sets.entries[i].base);
    free(envconf->sets.entries);
}