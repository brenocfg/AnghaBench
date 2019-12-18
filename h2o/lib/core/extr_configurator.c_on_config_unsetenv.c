#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; TYPE_3__** elements; } ;
struct TYPE_10__ {int /*<<< orphan*/  scalar; TYPE_1__ sequence; } ;
struct TYPE_11__ {int type; TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
struct TYPE_12__ {int /*<<< orphan*/  env; } ;
typedef  TYPE_4__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
#define  YOML_TYPE_SCALAR 129 
#define  YOML_TYPE_SEQUENCE 128 
 int /*<<< orphan*/  h2o_config_unsetenv (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  inherit_env_if_necessary (TYPE_4__*) ; 

__attribute__((used)) static int on_config_unsetenv(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    inherit_env_if_necessary(ctx);

    switch (node->type) {
    case YOML_TYPE_SCALAR:
        h2o_config_unsetenv(ctx->env, node->data.scalar);
        break;
    case YOML_TYPE_SEQUENCE: {
        size_t i;
        for (i = 0; i != node->data.sequence.size; ++i) {
            yoml_t *element = node->data.sequence.elements[i];
            if (element->type != YOML_TYPE_SCALAR) {
                h2o_configurator_errprintf(cmd, element, "element of a sequence passed to unsetenv must be a scalar");
                return -1;
            }
            h2o_config_unsetenv(ctx->env, element->data.scalar);
        }
    } break;
    default:
        h2o_configurator_errprintf(cmd, node, "argument to unsetenv must be either a scalar or a sequence");
        return -1;
    }

    return 0;
}