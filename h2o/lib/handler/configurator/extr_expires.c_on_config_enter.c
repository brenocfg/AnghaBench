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
struct expires_configurator_t {TYPE_1__** args; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
struct TYPE_2__ {scalar_t__ mode; } ;

/* Variables and functions */
 scalar_t__ H2O_EXPIRES_MODE_MAX_AGE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* h2o_mem_alloc (int) ; 

__attribute__((used)) static int on_config_enter(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct expires_configurator_t *self = (void *)_self;

    if (self->args[0] != NULL) {
        /* duplicate */
        assert(self->args[0]->mode == H2O_EXPIRES_MODE_MAX_AGE);
        self->args[1] = h2o_mem_alloc(sizeof(**self->args));
        *self->args[1] = *self->args[0];
    } else {
        self->args[1] = NULL;
    }
    ++self->args;
    return 0;
}