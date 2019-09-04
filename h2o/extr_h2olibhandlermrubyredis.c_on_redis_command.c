#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  command; } ;
struct st_h2o_mruby_redis_command_context_t {TYPE_4__ refs; TYPE_3__* client; } ;
struct RClass {int dummy; } ;
typedef  int /*<<< orphan*/  redisReply ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
struct TYPE_7__ {TYPE_2__* ctx; } ;
struct TYPE_6__ {TYPE_1__* shared; } ;
struct TYPE_5__ {int /*<<< orphan*/ * mrb; } ;

/* Variables and functions */
 int /*<<< orphan*/  decode_redis_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct RClass* get_error_class (int /*<<< orphan*/ *,char*) ; 
 char const* h2o_redis_error_command_timeout ; 
 char const* h2o_redis_error_connect_timeout ; 
 char const* h2o_redis_error_connection ; 
 char const* h2o_redis_error_protocol ; 
 int /*<<< orphan*/  mrb_exc_new (int /*<<< orphan*/ *,struct RClass*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_gc_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  pass_reply (struct st_h2o_mruby_redis_command_context_t*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void on_redis_command(redisReply *_reply, void *_ctx, const char *errstr)
{
    struct st_h2o_mruby_redis_command_context_t *ctx = _ctx;
    mrb_state *mrb = ctx->client->ctx->shared->mrb;
    mrb_value reply = mrb_nil_value();

    int gc_arena = mrb_gc_arena_save(mrb);

    if (errstr == NULL) {
        if (_reply == NULL)
            return;
        reply = decode_redis_reply(mrb, _reply, ctx->refs.command);
    } else {
        struct RClass *error_klass = NULL;

        if (errstr == h2o_redis_error_connection) {
            error_klass = get_error_class(mrb, "ConnectionError");
        } else if (errstr == h2o_redis_error_protocol) {
            error_klass = get_error_class(mrb, "ProtocolError");
        } else if (errstr == h2o_redis_error_connect_timeout) {
            error_klass = get_error_class(mrb, "ConnectTimeoutError");
        } else if (errstr == h2o_redis_error_command_timeout) {
            error_klass = get_error_class(mrb, "CommandTimeoutError");
        } else {
            error_klass = get_error_class(mrb, "UnknownError");
        }

        reply = mrb_exc_new(mrb, error_klass, errstr, strlen(errstr));
    }

    pass_reply(ctx, reply);

    mrb_gc_arena_restore(mrb, gc_arena);
    mrb_gc_unregister(mrb, ctx->refs.command);
}