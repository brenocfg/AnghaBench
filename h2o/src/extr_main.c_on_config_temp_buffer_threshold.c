#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_8__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_9__ {int threshold; } ;

/* Variables and functions */
 int SIZE_MAX ; 
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,TYPE_2__*,char*) ; 
 scalar_t__ h2o_configurator_scanf (int /*<<< orphan*/ *,TYPE_2__*,char*,int*) ; 
 TYPE_4__ h2o_socket_buffer_mmap_settings ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int on_config_temp_buffer_threshold(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    /* if "OFF", disable temp buffers by setting the threshold to SIZE_MAX */
    if (strcasecmp(node->data.scalar, "OFF") == 0) {
        h2o_socket_buffer_mmap_settings.threshold = SIZE_MAX;
        return 0;
    }

    /* if not "OFF", it could be a number */
    if (h2o_configurator_scanf(cmd, node, "%zu", &h2o_socket_buffer_mmap_settings.threshold) != 0)
        return -1;

    if (h2o_socket_buffer_mmap_settings.threshold < 1048576) {
        h2o_configurator_errprintf(cmd, node, "threshold is too low (must be >= 1048576; OFF to disable)");
        return -1;
    }

    return 0;
}