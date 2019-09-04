#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_7__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;
struct TYPE_9__ {int /*<<< orphan*/  crash_handler; } ;
struct TYPE_8__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 TYPE_5__ conf ; 
 TYPE_4__ h2o_strdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_config_crash_handler(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    conf.crash_handler = h2o_strdup(NULL, node->data.scalar, SIZE_MAX).base;
    return 0;
}