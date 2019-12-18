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
typedef  size_t mrb_int ;

/* Variables and functions */
 size_t RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (unsigned char) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,size_t*) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 

__attribute__((used)) static mrb_value
mrb_str_getbyte(mrb_state *mrb, mrb_value str)
{
  mrb_int pos;
  mrb_get_args(mrb, "i", &pos);

  if (pos < 0)
    pos += RSTRING_LEN(str);
  if (pos < 0 ||  RSTRING_LEN(str) <= pos)
    return mrb_nil_value();

  return mrb_fixnum_value((unsigned char)RSTRING_PTR(str)[pos]);
}