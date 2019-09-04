#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t size; TYPE_3__* entries; } ;
struct TYPE_5__ {TYPE_2__ unsets; } ;
typedef  TYPE_1__ h2o_envconf_t ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 scalar_t__ h2o_memis (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,size_t) ; 
 TYPE_3__ h2o_strdup_shared (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 size_t strlen (char const*) ; 

void h2o_config_unsetenv(h2o_envconf_t *envconf, const char *name)
{
    size_t i, name_len = strlen(name);

    /* do nothing if already set */
    for (i = 0; i != envconf->unsets.size; ++i)
        if (h2o_memis(envconf->unsets.entries[i].base, envconf->unsets.entries[i].len, name, name_len))
            return;
    /* register */
    h2o_vector_reserve(NULL, &envconf->unsets, envconf->unsets.size + 1);
    envconf->unsets.entries[envconf->unsets.size++] = h2o_strdup_shared(NULL, name, name_len);
}