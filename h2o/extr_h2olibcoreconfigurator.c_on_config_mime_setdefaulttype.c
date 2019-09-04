#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  scalar; } ;
struct TYPE_9__ {TYPE_1__ data; } ;
typedef  TYPE_2__ yoml_t ;
struct TYPE_10__ {int /*<<< orphan*/ * mimemap; } ;
typedef  TYPE_3__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_configurator_command_t ;

/* Variables and functions */
 scalar_t__ assert_is_mimetype (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  clone_mimemap_if_clean (TYPE_3__*) ; 
 int /*<<< orphan*/  h2o_mimemap_set_default_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_mime_setdefaulttype(h2o_configurator_command_t *cmd, h2o_configurator_context_t *ctx, yoml_t *node)
{
    if (assert_is_mimetype(cmd, node) != 0)
        return -1;

    clone_mimemap_if_clean(ctx);
    h2o_mimemap_set_default_type(*ctx->mimemap, node->data.scalar, NULL);

    return 0;
}