#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_15__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
struct TYPE_16__ {int /*<<< orphan*/  base; } ;
typedef  TYPE_3__ h2o_iovec_t ;
typedef  int /*<<< orphan*/  h2o_headers_command_when_t ;
typedef  int /*<<< orphan*/  h2o_headers_command_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 scalar_t__ add_cmd (int /*<<< orphan*/ *,TYPE_2__*,int,TYPE_3__*,TYPE_3__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ extract_name_value (int /*<<< orphan*/ ,TYPE_3__**,TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  h2o_iovec_is_token (TYPE_3__*) ; 
 scalar_t__ parse_header_node (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__***,size_t*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_header_2arg(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, int cmd_id, yoml_t *node,
                                 h2o_headers_command_t **headers_cmds)
{
    h2o_iovec_t *name, value;
    yoml_t **headers;
    size_t num_headers;
    h2o_headers_command_when_t when;

    if (parse_header_node(cmd, &node, &headers, &num_headers, &when) != 0)
        return -1;

    int i;
    for (i = 0; i != num_headers; ++i) {
        yoml_t *header = headers[i];
        if (extract_name_value(header->data.scalar, &name, &value) != 0) {
            h2o_configurator_errprintf(cmd, header, "failed to parse the value; should be in form of `name: value`");
            return -1;
        }
        if (add_cmd(cmd, header, cmd_id, name, value, when, headers_cmds) != 0) {
            if (!h2o_iovec_is_token(name))
                free(name->base);
            free(value.base);
            return -1;
        }
    }

    return 0;
}