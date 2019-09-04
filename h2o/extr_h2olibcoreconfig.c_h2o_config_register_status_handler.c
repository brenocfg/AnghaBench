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
typedef  int /*<<< orphan*/  h2o_status_handler_t ;
struct TYPE_5__ {size_t size; int /*<<< orphan*/ ** entries; } ;
struct TYPE_4__ {TYPE_2__ statuses; } ;
typedef  TYPE_1__ h2o_globalconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_2__*,int) ; 

void h2o_config_register_status_handler(h2o_globalconf_t *config, h2o_status_handler_t *status_handler)
{
    /* check if the status handler is already registered */
    size_t i;
    for (i = 0; i != config->statuses.size; ++i)
        if (config->statuses.entries[i] == status_handler)
            return;
    /* register the new handler */
    h2o_vector_reserve(NULL, &config->statuses, config->statuses.size + 1);
    config->statuses.entries[config->statuses.size++] = status_handler;
}