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
typedef  int /*<<< orphan*/  yoml_t ;
typedef  int /*<<< orphan*/  h2o_token_t ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_headers_command_when_t ;
typedef  int /*<<< orphan*/  h2o_headers_command_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  h2o_headers_append_command (int /*<<< orphan*/ **,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_headers_is_prohibited_name (int /*<<< orphan*/  const*) ; 
 scalar_t__ h2o_iovec_is_token (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int add_cmd(h2o_configurator_command_t *cmd, yoml_t *node, int cmd_id, h2o_iovec_t *name, h2o_iovec_t value,
                   h2o_headers_command_when_t when, h2o_headers_command_t **cmds)
{
    if (h2o_iovec_is_token(name)) {
        const h2o_token_t *token = (void *)name;
        if (h2o_headers_is_prohibited_name(token)) {
            h2o_configurator_errprintf(cmd, node, "the named header cannot be rewritten");
            return -1;
        }
    }

    h2o_headers_append_command(cmds, cmd_id, name, value, when);
    return 0;
}