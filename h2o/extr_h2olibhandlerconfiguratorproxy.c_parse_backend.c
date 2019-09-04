#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_12__ {int type; TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_url_t ;
typedef  int /*<<< orphan*/  h2o_socketpool_target_t ;
struct TYPE_13__ {unsigned int weight_m1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_3__ h2o_socketpool_target_conf_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 unsigned int H2O_SOCKETPOOL_TARGET_MAX_WEIGHT ; 
 int /*<<< orphan*/  SIZE_MAX ; 
#define  YOML_TYPE_MAPPING 129 
#define  YOML_TYPE_SCALAR 128 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  h2o_configurator_parse_mapping (int /*<<< orphan*/ *,TYPE_2__*,char*,char*,TYPE_2__***,TYPE_2__***) ; 
 int /*<<< orphan*/  h2o_configurator_scanf (int /*<<< orphan*/ *,TYPE_2__*,char*,unsigned int*) ; 
 int /*<<< orphan*/ * h2o_socketpool_create_target (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ h2o_url_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static h2o_socketpool_target_t *parse_backend(h2o_configurator_command_t *cmd, yoml_t *backend)
{
    yoml_t **url_node;
    h2o_socketpool_target_conf_t lb_per_target_conf = {0}; /* default weight of each target */

    switch (backend->type) {
    case YOML_TYPE_SCALAR:
        url_node = &backend;
        break;
    case YOML_TYPE_MAPPING: {
        yoml_t **weight_node;
        if (h2o_configurator_parse_mapping(cmd, backend, "url:s", "weight:*", &url_node, &weight_node) != 0)
            return NULL;
        if (weight_node != NULL) {
            unsigned weight;
            if (h2o_configurator_scanf(cmd, *weight_node, "%u", &weight) != 0)
                return NULL;
            if (!(1 <= weight && weight <= H2O_SOCKETPOOL_TARGET_MAX_WEIGHT)) {
                h2o_configurator_errprintf(cmd, *weight_node, "weight must be an integer in range 1 - 256");
                return NULL;
            }
            lb_per_target_conf.weight_m1 = weight - 1;
        }
    } break;
    default:
        h2o_configurator_errprintf(cmd, backend,
                                   "items of arguments passed to proxy.reverse.url must be either a scalar or a mapping");
        return NULL;
    }

    h2o_url_t url;
    if (h2o_url_parse((*url_node)->data.scalar, SIZE_MAX, &url) != 0) {
        h2o_configurator_errprintf(cmd, *url_node, "failed to parse URL: %s\n", (*url_node)->data.scalar);
        return NULL;
    }
    return h2o_socketpool_create_target(&url, &lb_per_target_conf);
}