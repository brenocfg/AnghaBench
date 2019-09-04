#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {size_t size; TYPE_3__** elements; } ;
struct TYPE_18__ {int /*<<< orphan*/  scalar; TYPE_1__ sequence; } ;
struct TYPE_19__ {int type; TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
struct errordoc_configurator_t {TYPE_8__* vars; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  h2o_iovec_t ;
struct TYPE_20__ {int status; int /*<<< orphan*/  url; } ;
typedef  TYPE_4__ h2o_errordoc_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_21__ {scalar_t__ configurator; } ;
typedef  TYPE_5__ h2o_configurator_command_t ;
struct TYPE_22__ {scalar_t__ size; TYPE_4__* entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
#define  YOML_TYPE_SCALAR 129 
#define  YOML_TYPE_SEQUENCE 128 
 int* alloca (int) ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (TYPE_5__*,TYPE_3__*,char*,...) ; 
 scalar_t__ h2o_configurator_parse_mapping (TYPE_5__*,TYPE_3__*,char*,int /*<<< orphan*/ *,TYPE_3__***,TYPE_3__***) ; 
 scalar_t__ h2o_configurator_scanf (TYPE_5__*,TYPE_3__*,char*,int*) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_8__*,scalar_t__) ; 

__attribute__((used)) static int register_errordoc(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *hash)
{
    struct errordoc_configurator_t *self = (void *)cmd->configurator;
    yoml_t **url_node, **status_nodes;
    size_t i, j, num_status;

    /* extract the nodes to handle */
    if (h2o_configurator_parse_mapping(cmd, hash, "url:s,status:*", NULL, &url_node, &status_nodes) != 0)
        return -1;
    switch ((*status_nodes)->type) {
    case YOML_TYPE_SCALAR:
        num_status = 1;
        break;
    case YOML_TYPE_SEQUENCE:
        if ((*status_nodes)->data.sequence.size == 0) {
            h2o_configurator_errprintf(cmd, *status_nodes, "status cannot be an empty sequence");
            return -1;
        }
        num_status = (*status_nodes)->data.sequence.size;
        status_nodes = (*status_nodes)->data.sequence.elements;
        break;
    default:
        h2o_configurator_errprintf(cmd, *status_nodes, "status must be a 3-digit scalar or a sequence of 3-digit scalars");
        return -1;
    }

    /* convert list of status_nodes (in string) to list of 3-digit codes */
    int *status_codes = alloca(sizeof(*status_codes) * num_status);
    for (i = 0; i != num_status; ++i) {
        if (h2o_configurator_scanf(cmd, status_nodes[i], "%d", &status_codes[i]) != 0)
            return -1;
        if (!(400 <= status_codes[i] && status_codes[i] <= 599)) {
            h2o_configurator_errprintf(cmd, status_nodes[i], "status must be within range of 400 to 599");
            return -1;
        }
        /* check the scanned status hasn't already appeared */
        for (j = 0; j != i; ++j) {
            if (status_codes[j] == status_codes[i]) {
                h2o_configurator_errprintf(cmd, status_nodes[i], "status %d appears multiple times", status_codes[i]);
                return -1;
            }
        }
    }

    h2o_iovec_t url = h2o_strdup(&self->pool, (*url_node)->data.scalar, SIZE_MAX);
    for (i = 0; i != num_status; ++i) {
        /* register */
        h2o_vector_reserve(&self->pool, self->vars, self->vars->size + 1);
        h2o_errordoc_t *errordoc = self->vars->entries + self->vars->size++;
        errordoc->status = status_codes[i];
        errordoc->url = url;
    }

    return 0;
}