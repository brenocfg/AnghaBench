#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct compress_configurator_t {TYPE_5__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_7__ {scalar_t__ configurator; } ;
typedef  TYPE_2__ h2o_configurator_command_t ;
struct TYPE_6__ {int /*<<< orphan*/  quality; } ;
struct TYPE_8__ {TYPE_1__ gzip; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_GZIP_QUALITY ; 
 TYPE_5__ all_off ; 
 scalar_t__ h2o_configurator_get_one_of (TYPE_2__*,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int on_config_gzip(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct compress_configurator_t *self = (void *)cmd->configurator;
    int mode;

    if ((mode = (int)h2o_configurator_get_one_of(cmd, node, "OFF,ON")) == -1)
        return -1;

    *self->vars = all_off;
    if (mode != 0)
        self->vars->gzip.quality = DEFAULT_GZIP_QUALITY;

    return 0;
}