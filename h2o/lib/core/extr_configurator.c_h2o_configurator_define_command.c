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
struct TYPE_7__ {scalar_t__ size; TYPE_2__* entries; } ;
struct TYPE_5__ {TYPE_3__ commands; } ;
typedef  TYPE_1__ h2o_configurator_t ;
struct TYPE_6__ {int flags; char const* name; int /*<<< orphan*/  cb; TYPE_1__* configurator; } ;
typedef  TYPE_2__ h2o_configurator_command_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_cb ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__) ; 

void h2o_configurator_define_command(h2o_configurator_t *configurator, const char *name, int flags, h2o_configurator_command_cb cb)
{
    h2o_configurator_command_t *cmd;

    h2o_vector_reserve(NULL, &configurator->commands, configurator->commands.size + 1);
    cmd = configurator->commands.entries + configurator->commands.size++;
    cmd->configurator = configurator;
    cmd->flags = flags;
    cmd->name = name;
    cmd->cb = cb;
}