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
struct st_h2o_mruby_redis_client_t {int /*<<< orphan*/  super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct st_h2o_mruby_redis_client_t* DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_redis_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value disconnect_method(mrb_state *mrb, mrb_value self)
{
    struct st_h2o_mruby_redis_client_t *client = DATA_PTR(self);
    h2o_redis_disconnect(&client->super);
    return self;
}