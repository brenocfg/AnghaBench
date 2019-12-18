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
struct TYPE_2__ {int /*<<< orphan*/  on_req; } ;
struct st_h2o_http2_debug_state_handler_t {int hpack_enabled; TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  h2o_pathconf_t ;
typedef  int /*<<< orphan*/  h2o_hostconf_t ;

/* Variables and functions */
 int /*<<< orphan*/ * h2o_config_register_path (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ h2o_create_handler (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  on_req ; 

void h2o_http2_debug_state_register(h2o_hostconf_t *conf, int hpack_enabled)
{
    h2o_pathconf_t *pathconf = h2o_config_register_path(conf, "/.well-known/h2/state", 0);
    struct st_h2o_http2_debug_state_handler_t *self = (void *)h2o_create_handler(pathconf, sizeof(*self));
    self->super.on_req = on_req;
    self->hpack_enabled = hpack_enabled;
}