#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
struct TYPE_4__ {int pos; char* base; int len; } ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */
 TYPE_1__* DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_is_open (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_cat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
mrb_input_stream_read(mrb_state *mrb, mrb_value self)
{
  mrb_int len;
  mrb_value buf;
  mrb_int n = mrb_get_args(mrb, "|iS", &len, &buf), pos;
  mrb_input_stream_t *stream = DATA_PTR(self);
  const char *start;

  assert_is_open(mrb, stream);

  pos = stream->pos;
  start = stream->base + pos;

  if (pos >= stream->len) {
    return n == 0 ? mrb_str_new_lit(mrb, "") : mrb_nil_value();
  }
  if (n == 0) {
    stream->pos = stream->len;
    return mrb_str_new(mrb, start, stream->len - pos);
  } else {
    mrb_int newpos = pos + len;
    if (newpos > stream->len) {
      newpos = stream->len;
    }
    stream->pos = newpos;
    if (n == 1) {
      return mrb_str_new(mrb, start, newpos - pos);
    } else {
      return mrb_str_cat(mrb, buf, start, newpos - pos);
    }
  }
}