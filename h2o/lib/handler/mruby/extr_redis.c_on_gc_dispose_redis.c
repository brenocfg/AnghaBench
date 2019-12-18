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
struct TYPE_2__ {int /*<<< orphan*/  redis; } ;
struct st_h2o_mruby_redis_client_t {int /*<<< orphan*/  super; TYPE_1__ refs; } ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  h2o_redis_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static void on_gc_dispose_redis(mrb_state *mrb, void *_client)
{
    struct st_h2o_mruby_redis_client_t *client = _client;

    client->refs.redis = mrb_nil_value();
    h2o_redis_free(&client->super);
}