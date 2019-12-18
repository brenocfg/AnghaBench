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
 scalar_t__ mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_float_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_istruct_ptr (int /*<<< orphan*/ ) ; 
 int mrb_istruct_size () ; 
 scalar_t__ mrb_string_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 

__attribute__((used)) static mrb_value
istruct_test_initialize(mrb_state *mrb, mrb_value self)
{
  char *string = (char*)mrb_istruct_ptr(self);
  mrb_int size = mrb_istruct_size();
  mrb_value object;
  mrb_get_args(mrb, "o", &object);

  if (mrb_fixnum_p(object)) {
    strncpy(string, "fixnum", size-1);
  }
#ifndef MRB_WITHOUT_FLOAT
  else if (mrb_float_p(object)) {
    strncpy(string, "float", size-1);
  }
#endif
  else if (mrb_string_p(object)) {
    strncpy(string, "string", size-1);
  }
  else {
    strncpy(string, "anything", size-1);
  }

  string[size - 1] = 0; // force NULL at the end
  return self;
}