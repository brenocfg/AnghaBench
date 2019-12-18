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
typedef  int /*<<< orphan*/  mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_fixnum_value (int /*<<< orphan*/ ) ; 
 char* mrb_sym2name_len (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_symbol (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_utf8_len (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
mrb_sym_length(mrb_state *mrb, mrb_value self)
{
  mrb_int len;
#ifdef MRB_UTF8_STRING
  mrb_int byte_len;
  const char *name = mrb_sym2name_len(mrb, mrb_symbol(self), &byte_len);
  len = mrb_utf8_len(name, byte_len);
#else
  mrb_sym2name_len(mrb, mrb_symbol(self), &len);
#endif
  return mrb_fixnum_value(len);
}