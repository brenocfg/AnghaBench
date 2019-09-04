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

/* Variables and functions */
 int /*<<< orphan*/  E_INDEX_ERROR ; 
 int RSTRING_LEN (int /*<<< orphan*/ ) ; 
 unsigned char* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (unsigned char) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int*,int*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_str_setbyte(mrb_state *mrb, mrb_value str)
{
  mrb_int pos, byte;
  mrb_int len;

  mrb_get_args(mrb, "ii", &pos, &byte);

  len = RSTRING_LEN(str);
  if (pos < -len || len <= pos)
    mrb_raisef(mrb, E_INDEX_ERROR, "index %S is out of array", mrb_fixnum_value(pos));
  if (pos < 0)
    pos += len;

  mrb_str_modify(mrb, mrb_str_ptr(str));
  byte &= 0xff;
  RSTRING_PTR(str)[pos] = (unsigned char)byte;
  return mrb_fixnum_value((unsigned char)byte);
}