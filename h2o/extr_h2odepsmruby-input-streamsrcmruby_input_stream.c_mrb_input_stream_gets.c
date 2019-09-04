#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
struct TYPE_5__ {scalar_t__ pos; scalar_t__ len; scalar_t__ base; } ;
typedef  TYPE_1__ mrb_input_stream_t ;

/* Variables and functions */
 TYPE_1__* DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_is_open (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ seek_char (TYPE_1__*,char) ; 

__attribute__((used)) static mrb_value
mrb_input_stream_gets(mrb_state *mrb, mrb_value self)
{
  mrb_input_stream_t *stream = DATA_PTR(self);
  mrb_int pos, len;

  assert_is_open(mrb, stream);

  pos = stream->pos;
  len = seek_char(stream, '\n');
  if (len < 0) {
    return mrb_nil_value();
  }
  if (stream->pos + len < stream->len) {
    len++;
  }
  stream->pos += len;
  return mrb_str_new(mrb, (stream->base + pos), len);
}