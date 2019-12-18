#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct st_h2o_specific_file_handler_t {TYPE_3__* mime_type; } ;
typedef  int /*<<< orphan*/  h2o_handler_t ;
typedef  int /*<<< orphan*/  h2o_context_t ;
struct TYPE_4__ {int /*<<< orphan*/  pathconf; } ;
struct TYPE_5__ {TYPE_1__ dynamic; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ data; } ;

/* Variables and functions */
 scalar_t__ H2O_MIMEMAP_TYPE_DYNAMIC ; 
 int /*<<< orphan*/  h2o_context_dispose_pathconf_context (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void specific_handler_on_context_dispose(h2o_handler_t *_self, h2o_context_t *ctx)
{
    struct st_h2o_specific_file_handler_t *self = (void *)_self;

    if (self->mime_type->type == H2O_MIMEMAP_TYPE_DYNAMIC)
        h2o_context_dispose_pathconf_context(ctx, &self->mime_type->data.dynamic.pathconf);
}