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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {scalar_t__ state; } ;
struct st_h2o_mruby_redis_client_t {TYPE_1__ super; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 struct st_h2o_mruby_redis_client_t* DATA_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ H2O_REDIS_CONNECTION_STATE_CLOSED ; 
 int /*<<< orphan*/  h2o_redis_connect (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* mrb_string_value_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static mrb_value connect_method(mrb_state *mrb, mrb_value self)
{
    struct st_h2o_mruby_redis_client_t *client = DATA_PTR(self);
    if (client->super.state != H2O_REDIS_CONNECTION_STATE_CLOSED)
        return self;

    mrb_value _host = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@host"));
    mrb_value _port = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@port"));
    const char *host = mrb_string_value_cstr(mrb, &_host);
    uint16_t port = mrb_fixnum(_port);

    h2o_redis_connect(&client->super, host, port);

    return self;
}