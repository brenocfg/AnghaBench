#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct st_h2o_access_log_configurator_t {TYPE_1__* handles; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
typedef  int /*<<< orphan*/  h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_access_log_filehandle_t ;
struct TYPE_3__ {int size; int /*<<< orphan*/ ** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_mem_addref_shared (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_vector_reserve (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int on_config_enter(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_h2o_access_log_configurator_t *self = (void *)_self;
    size_t i;

    /* push the stack pointer */
    ++self->handles;

    /* link the handles */
    memset(self->handles, 0, sizeof(*self->handles));
    h2o_vector_reserve(NULL, self->handles, self->handles[-1].size + 1);
    for (i = 0; i != self->handles[-1].size; ++i) {
        h2o_access_log_filehandle_t *fh = self->handles[-1].entries[i];
        self->handles[0].entries[self->handles[0].size++] = fh;
        h2o_mem_addref_shared(fh);
    }

    return 0;
}