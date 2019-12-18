#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct st_h2o_file_configurator_t {TYPE_1__* vars; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  index_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  dup_strlist (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int on_config_enter(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_h2o_file_configurator_t *self = (void *)_self;
    ++self->vars;
    self->vars[0].index_files = dup_strlist(self->vars[-1].index_files);
    self->vars[0].flags = self->vars[-1].flags;
    return 0;
}