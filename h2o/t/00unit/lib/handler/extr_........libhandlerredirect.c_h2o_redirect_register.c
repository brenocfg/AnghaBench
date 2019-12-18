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
struct TYPE_4__ {int /*<<< orphan*/  on_req; int /*<<< orphan*/  dispose; } ;
struct TYPE_5__ {int internal; int status; int /*<<< orphan*/  prefix; TYPE_1__ super; } ;
typedef  TYPE_2__ h2o_redirect_handler_t ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;

/* Variables and functions */
 int /*<<< orphan*/  SIZE_MAX ; 
 scalar_t__ h2o_create_handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  h2o_strdup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_dispose ; 
 int /*<<< orphan*/  on_req ; 

h2o_redirect_handler_t *h2o_redirect_register(h2o_pathconf_t *pathconf, int internal, int status, const char *prefix)
{
    h2o_redirect_handler_t *self = (void *)h2o_create_handler(pathconf, sizeof(*self));
    self->super.dispose = on_dispose;
    self->super.on_req = on_req;
    self->internal = internal;
    self->status = status;
    self->prefix = h2o_strdup(NULL, prefix, SIZE_MAX);
    return self;
}