#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_9__ ;
typedef  struct TYPE_30__   TYPE_8__ ;
typedef  struct TYPE_29__   TYPE_7__ ;
typedef  struct TYPE_28__   TYPE_6__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {size_t size; TYPE_7__** elements; } ;
struct TYPE_24__ {TYPE_1__ sequence; } ;
struct TYPE_29__ {scalar_t__ type; TYPE_2__ data; } ;
typedef  TYPE_7__ yoml_t ;
struct TYPE_25__ {int size; } ;
struct TYPE_26__ {TYPE_3__ handlers; } ;
struct TYPE_27__ {TYPE_4__ pathconf; } ;
struct TYPE_28__ {TYPE_5__ dynamic; } ;
struct TYPE_30__ {TYPE_6__ data; } ;
typedef  TYPE_8__ h2o_mimemap_type_t ;
struct TYPE_31__ {int /*<<< orphan*/ * mimemap; TYPE_4__* pathconf; int /*<<< orphan*/  globalconf; } ;
typedef  TYPE_9__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_CONFIGURATOR_FLAG_EXTENSION ; 
 scalar_t__ YOML_TYPE_MAPPING ; 
#define  YOML_TYPE_SCALAR 129 
#define  YOML_TYPE_SEQUENCE 128 
 char** alloca (int) ; 
 int /*<<< orphan*/  clone_mimemap_if_clean (TYPE_9__*) ; 
 TYPE_9__* create_context (TYPE_9__*,int) ; 
 int /*<<< orphan*/  destroy_context (TYPE_9__*) ; 
 int h2o_configurator_apply_commands (TYPE_9__*,TYPE_7__*,int /*<<< orphan*/ ,char const**) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_7__*,char*) ; 
 TYPE_8__* h2o_mimemap_define_dynamic (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 char* normalize_ext (int /*<<< orphan*/ *,TYPE_7__*) ; 
 TYPE_7__* yoml_get (TYPE_7__*,char*) ; 

__attribute__((used)) static int on_config_custom_handler(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    static const char *ignore_commands[] = {"extension", NULL};
    yoml_t *ext_node;
    const char **exts;
    h2o_mimemap_type_t *type = NULL;

    if (node->type != YOML_TYPE_MAPPING) {
        h2o_configurator_errprintf(cmd, node, "argument must be a MAPPING");
        return -1;
    }
    if ((ext_node = yoml_get(node, "extension")) == NULL) {
        h2o_configurator_errprintf(cmd, node, "mandatory key `extension` is missing");
        return -1;
    }

    /* create dynamic type */
    switch (ext_node->type) {
    case YOML_TYPE_SCALAR:
        exts = alloca(2 * sizeof(*exts));
        if ((exts[0] = normalize_ext(cmd, ext_node)) == NULL)
            return -1;
        exts[1] = NULL;
        break;
    case YOML_TYPE_SEQUENCE: {
        exts = alloca((ext_node->data.sequence.size + 1) * sizeof(*exts));
        size_t i;
        for (i = 0; i != ext_node->data.sequence.size; ++i) {
            yoml_t *n = ext_node->data.sequence.elements[i];
            if ((exts[i] = normalize_ext(cmd, n)) == NULL)
                return -1;
        }
        exts[i] = NULL;
    } break;
    default:
        h2o_configurator_errprintf(cmd, ext_node, "`extensions` must be a scalar or sequence of scalar");
        return -1;
    }
    clone_mimemap_if_clean(ctx);
    type = h2o_mimemap_define_dynamic(*ctx->mimemap, exts, ctx->globalconf);

    /* apply the configuration commands */
    h2o_configurator_context_t *ext_ctx = create_context(ctx, 1);
    ext_ctx->pathconf = &type->data.dynamic.pathconf;
    ext_ctx->mimemap = NULL;
    int cmd_ret = h2o_configurator_apply_commands(ext_ctx, node, H2O_CONFIGURATOR_FLAG_EXTENSION, ignore_commands);
    destroy_context(ext_ctx);
    if (cmd_ret != 0)
        return cmd_ret;
    switch (type->data.dynamic.pathconf.handlers.size) {
    case 1:
        break;
    case 0:
        h2o_configurator_errprintf(cmd, node, "no handler declared for given extension");
        return -1;
    default:
        h2o_configurator_errprintf(cmd, node, "cannot assign more than one handler for given extension");
        return -1;
    }

    return 0;
}