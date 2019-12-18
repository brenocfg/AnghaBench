#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_headers_filter_t {TYPE_1__* cmds; } ;
struct TYPE_2__ {scalar_t__ cmd; scalar_t__ when; } ;
typedef  TYPE_1__ h2o_headers_command_t ;

/* Variables and functions */
 scalar_t__ H2O_HEADERS_CMD_NULL ; 
 scalar_t__ H2O_HEADERS_CMD_UNSET ; 
 scalar_t__ H2O_HEADERS_CMD_WHEN_FINAL ; 

__attribute__((used)) static int requires_early_hints_handler(struct st_headers_filter_t *self)
{
    h2o_headers_command_t *cmd;
    for (cmd = self->cmds; cmd->cmd != H2O_HEADERS_CMD_NULL; ++cmd) {
        if (cmd->cmd != H2O_HEADERS_CMD_UNSET && cmd->when != H2O_HEADERS_CMD_WHEN_FINAL)
            return 1;
    }
    return 0;
}