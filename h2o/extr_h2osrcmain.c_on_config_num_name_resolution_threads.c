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
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_configurator_errprintf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ h2o_configurator_scanf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 scalar_t__ h2o_hostinfo_max_threads ; 

__attribute__((used)) static int on_config_num_name_resolution_threads(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    if (h2o_configurator_scanf(cmd, node, "%zu", &h2o_hostinfo_max_threads) != 0)
        return -1;
    if (h2o_hostinfo_max_threads == 0) {
        h2o_configurator_errprintf(cmd, node, "num-name-resolution-threads must be >=1");
        return -1;
    }
    return 0;
}