#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {size_t size; int /*<<< orphan*/ * elements; } ;
struct TYPE_10__ {TYPE_1__ sequence; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_2__ data; } ;
typedef  TYPE_3__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_12__ {scalar_t__ size; int* entries; } ;
struct TYPE_13__ {TYPE_5__ thread_map; } ;

/* Variables and functions */
 scalar_t__ YOML_TYPE_SCALAR ; 
 scalar_t__ YOML_TYPE_SEQUENCE ; 
 TYPE_8__ conf ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_3__*,char*) ; 
 scalar_t__ h2o_configurator_scanf (int /*<<< orphan*/ *,TYPE_3__*,char*,size_t*) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_5__*,size_t) ; 
 scalar_t__ on_config_num_threads_add_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_config_num_threads(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    conf.thread_map.size = 0;
    if (node->type == YOML_TYPE_SCALAR) {
        size_t i, num_threads = 0;
        if (h2o_configurator_scanf(cmd, node, "%zu", &num_threads) != 0)
            return -1;
        h2o_vector_reserve(NULL, &conf.thread_map, num_threads);
        for (i = 0; i < num_threads; i++)
            conf.thread_map.entries[conf.thread_map.size++] = -1;
    } else if (node->type == YOML_TYPE_SEQUENCE) {
        /* a sequence is treated as a list of CPUs to bind to, one per thread to instantiate */
#ifdef H2O_HAS_PTHREAD_SETAFFINITY_NP
        size_t i;
        for (i = 0; i < node->data.sequence.size; i++) {
            if (on_config_num_threads_add_cpu(cmd, ctx, node->data.sequence.elements[i]) != 0)
                return -1;
        }
#else
        h2o_configurator_errprintf(
            cmd, node, "Can't handle a CPU list, this platform doesn't support thread pinning via `pthread_setaffinity_np`");
        return -1;
#endif
    }
    if (conf.thread_map.size == 0) {
        h2o_configurator_errprintf(cmd, node, "num-threads must be >=1");
        return -1;
    }
    return 0;
}