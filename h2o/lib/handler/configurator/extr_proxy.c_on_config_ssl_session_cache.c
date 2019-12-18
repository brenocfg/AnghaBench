#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_17__ {int type; TYPE_1__ data; } ;
typedef  TYPE_3__ yoml_t ;
typedef  int uint64_t ;
struct proxy_configurator_t {TYPE_2__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_18__ {scalar_t__ configurator; } ;
typedef  TYPE_4__ h2o_configurator_command_t ;
typedef  int /*<<< orphan*/  h2o_cache_t ;
struct TYPE_16__ {int /*<<< orphan*/  ssl_ctx; } ;

/* Variables and functions */
 size_t H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_CAPACITY ; 
 int H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_DURATION ; 
#define  YOML_TYPE_MAPPING 129 
#define  YOML_TYPE_SCALAR 128 
 int /*<<< orphan*/ * create_ssl_session_cache (size_t,int) ; 
 size_t h2o_cache_get_capacity (int /*<<< orphan*/ *) ; 
 int h2o_cache_get_duration (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (TYPE_4__*,TYPE_3__*,char*) ; 
 int /*<<< orphan*/  h2o_configurator_parse_mapping (TYPE_4__*,TYPE_3__*,char*,int /*<<< orphan*/ *,TYPE_3__***,TYPE_3__***) ; 
 int /*<<< orphan*/  h2o_configurator_scanf (TYPE_4__*,TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/ * h2o_socket_ssl_get_session_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_ssl_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int on_config_ssl_session_cache(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct proxy_configurator_t *self = (void *)cmd->configurator;
    size_t capacity = 0;
    uint64_t duration = 0;
    h2o_cache_t *current_cache = h2o_socket_ssl_get_session_cache(self->vars->ssl_ctx);

    switch (node->type) {
    case YOML_TYPE_SCALAR:
        if (strcasecmp(node->data.scalar, "OFF") == 0) {
            if (current_cache != NULL) {
                /* set the cache NULL */
                h2o_cache_t *empty_cache = NULL;
                update_ssl_ctx(&self->vars->ssl_ctx, NULL, -1, &empty_cache);
            }
            return 0;
        } else if (strcasecmp(node->data.scalar, "ON") == 0) {
            /* use default values */
            capacity = H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_CAPACITY;
            duration = H2O_DEFAULT_PROXY_SSL_SESSION_CACHE_DURATION;
        } else {
            h2o_configurator_errprintf(cmd, node, "scalar argument must be either of: `OFF`, `ON`");
            return -1;
        }
        break;
    case YOML_TYPE_MAPPING: {
        yoml_t **capacity_node, **lifetime_node;
        if (h2o_configurator_parse_mapping(cmd, node, "capacity:*,lifetime:*", NULL, &capacity_node, &lifetime_node) != 0)
            return -1;
        if (h2o_configurator_scanf(cmd, *capacity_node, "%zu", &capacity) != 0)
            return -1;
        if (capacity == 0) {
            h2o_configurator_errprintf(cmd, *capacity_node, "capacity must be greater than zero");
            return -1;
        }
        unsigned lifetime = 0;
        if (h2o_configurator_scanf(cmd, *lifetime_node, "%u", &lifetime) != 0)
            return -1;
        if (lifetime == 0) {
            h2o_configurator_errprintf(cmd, *lifetime_node, "lifetime must be greater than zero");
            return -1;
        }
        duration = (uint64_t)lifetime * 1000;
    } break;
    default:
        h2o_configurator_errprintf(cmd, node, "node must be a scalar or a mapping");
        return -1;
    }

    if (current_cache != NULL) {
        size_t current_capacity = h2o_cache_get_capacity(current_cache);
        uint64_t current_duration = h2o_cache_get_duration(current_cache);
        if (capacity == current_capacity && duration == current_duration) {
            /* parameters aren't changed, so reuse it */
            return 0;
        }
    }

    h2o_cache_t *new_cache = create_ssl_session_cache(capacity, duration);
    update_ssl_ctx(&self->vars->ssl_ctx, NULL, -1, &new_cache);
    return 0;
}