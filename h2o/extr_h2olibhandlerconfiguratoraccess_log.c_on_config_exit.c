#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  yoml_t ;
struct st_h2o_access_log_configurator_t {TYPE_1__* handles; } ;
typedef  int /*<<< orphan*/  h2o_configurator_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pathconf; } ;
typedef  TYPE_2__ h2o_configurator_context_t ;
typedef  int /*<<< orphan*/  h2o_access_log_filehandle_t ;
struct TYPE_4__ {size_t size; int /*<<< orphan*/ ** entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  h2o_access_log_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  h2o_mem_release_shared (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int on_config_exit(h2o_configurator_t *_self, h2o_configurator_context_t *ctx, yoml_t *node)
{
    struct st_h2o_access_log_configurator_t *self = (void *)_self;
    size_t i;

    /* register all handles, and decref them */
    for (i = 0; i != self->handles->size; ++i) {
        h2o_access_log_filehandle_t *fh = self->handles->entries[i];
        if (ctx->pathconf != NULL)
            h2o_access_log_register(ctx->pathconf, fh);
        h2o_mem_release_shared(fh);
    }
    /* free the vector */
    free(self->handles->entries);

    /* pop the stack pointer */
    --self->handles;

    return 0;
}