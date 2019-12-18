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
struct TYPE_2__ {scalar_t__ state; } ;
struct st_h2o_mruby_redis_client_t {TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct st_h2o_mruby_redis_client_t* DATA_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 int /*<<< orphan*/  mrb_bool_value (int) ; 

__attribute__((used)) static mrb_value disconnected_method(mrb_state *mrb, mrb_value self)
{
    struct st_h2o_mruby_redis_client_t *client = DATA_PTR(self);
    return mrb_bool_value(client->super.state == H2O_REDIS_CONNECTION_STATE_CLOSED);
}