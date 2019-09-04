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
struct TYPE_3__ {int type; size_t elements; int /*<<< orphan*/  len; int /*<<< orphan*/  str; int /*<<< orphan*/  integer; struct TYPE_3__** element; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
#define  REDIS_REPLY_ARRAY 133 
#define  REDIS_REPLY_ERROR 132 
#define  REDIS_REPLY_INTEGER 131 
#define  REDIS_REPLY_NIL 130 
#define  REDIS_REPLY_STATUS 129 
#define  REDIS_REPLY_STRING 128 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  get_error_class (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_ary_new_capa (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_ary_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (size_t) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value decode_redis_reply(mrb_state *mrb, redisReply *reply, mrb_value command)
{
    mrb_value decoded;

    switch (reply->type) {
    case REDIS_REPLY_STRING:
    case REDIS_REPLY_STATUS:
        decoded = mrb_str_new(mrb, reply->str, reply->len);
        break;
    case REDIS_REPLY_ARRAY:
        decoded = mrb_ary_new_capa(mrb, (mrb_int)reply->elements);
        mrb_int i;
        for (i = 0; i != reply->elements; ++i)
            mrb_ary_set(mrb, decoded, i, decode_redis_reply(mrb, reply->element[i], command));
        break;
    case REDIS_REPLY_INTEGER:
        decoded = mrb_fixnum_value((mrb_int)reply->integer);
        break;
    case REDIS_REPLY_NIL:
        decoded = mrb_nil_value();
        break;
    case REDIS_REPLY_ERROR: {
        mrb_value error_klass = mrb_obj_value(get_error_class(mrb, "CommandError"));
        decoded = mrb_funcall(mrb, error_klass, "new", 2, mrb_str_new(mrb, reply->str, reply->len), command);
    } break;
    default:
        assert(!"FIXME");
    }

    return decoded;
}