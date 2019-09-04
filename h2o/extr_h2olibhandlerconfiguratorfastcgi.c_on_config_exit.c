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
struct fastcgi_configurator_t {int /*<<< orphan*/  vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;

/* Variables and functions */

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct fastcgi_configurator_t *self = (void *)_self;

    --self->vars;
    return 0;
}