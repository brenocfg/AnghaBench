#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proxy_configurator_t {TYPE_2__* vars; } ;
typedef  int /*<<< orphan*/  h2o_headers_command_t ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_3__ {int /*<<< orphan*/ * headers_cmds; } ;
struct TYPE_4__ {TYPE_1__ conf; } ;

/* Variables and functions */

__attribute__((used)) static h2o_headers_command_t **get_headers_commands(h2o_configurator_t *_self)
{
    struct proxy_configurator_t *self = (void *)_self;
    return &self->vars->conf.headers_cmds;
}