#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t size; TYPE_3__** elements; } ;
struct TYPE_11__ {TYPE_1__ sequence; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_headers_command_when_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_HEADERS_CMD_WHEN_ALL ; 
 int /*<<< orphan*/  H2O_HEADERS_CMD_WHEN_EARLY ; 
 int /*<<< orphan*/  H2O_HEADERS_CMD_WHEN_FINAL ; 
 scalar_t__ YOML_TYPE_SCALAR ; 
 scalar_t__ YOML_TYPE_SEQUENCE ; 
 int h2o_configurator_get_one_of (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 scalar_t__ h2o_configurator_parse_mapping (int /*<<< orphan*/ *,TYPE_3__*,char*,char*,TYPE_3__***,TYPE_3__***) ; 

__attribute__((used)) static int parse_header_node(h2o_configurator_command_t *cmd, yoml_t **node, yoml_t ***headers, size_t *num_headers,
                             h2o_headers_command_when_t *when)
{

    if ((*node)->type == YOML_TYPE_SCALAR) {
        *headers = node;
        *num_headers = 1;
        *when = H2O_HEADERS_CMD_WHEN_FINAL;
    } else {
        yoml_t **header_node;
        yoml_t **when_node = NULL;
        if (h2o_configurator_parse_mapping(cmd, *node, "header:sa", "when:*", &header_node, &when_node) != 0)
            return -1;
        if ((*header_node)->type == YOML_TYPE_SEQUENCE) {
            *headers = (*header_node)->data.sequence.elements;
            *num_headers = (*header_node)->data.sequence.size;
        } else {
            *headers = header_node;
            *num_headers = 1;
        }
        if (when_node == NULL) {
            *when = H2O_HEADERS_CMD_WHEN_FINAL;
        } else {
            switch (h2o_configurator_get_one_of(cmd, *when_node, "final,early,all")) {
            case 0:
                *when = H2O_HEADERS_CMD_WHEN_FINAL;
                break;
            case 1:
                *when = H2O_HEADERS_CMD_WHEN_EARLY;
                break;
            case 2:
                *when = H2O_HEADERS_CMD_WHEN_ALL;
                break;
            default:
                return -1;
            }
        }
    }
    return 0;
}