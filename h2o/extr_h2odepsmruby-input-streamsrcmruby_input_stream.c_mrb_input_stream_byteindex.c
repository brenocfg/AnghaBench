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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int mrb_int ;
typedef  int /*<<< orphan*/  mrb_input_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/ * DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  assert_is_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int seek_char (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mrb_value
mrb_input_stream_byteindex(mrb_state *mrb, mrb_value self)
{
  mrb_input_stream_t *stream = DATA_PTR(self);
  mrb_int chr, n, len;

  assert_is_open(mrb, stream);

  n = mrb_get_args(mrb, "i", &chr);
  if (n != 1) {
    mrb_raisef(mrb, E_ARGUMENT_ERROR, "wrong number of arguments (%S for 1)", mrb_fixnum_value(n));
  }
  if (chr < 0 || chr > 255) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "index should be a byte (0 - 255)");
  }

  len = seek_char(stream, chr);
  if (len < 0) {
    return mrb_nil_value();
  }

  return mrb_fixnum_value(len);
}