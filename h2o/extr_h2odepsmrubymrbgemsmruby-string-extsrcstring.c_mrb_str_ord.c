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

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 scalar_t__* RSTRING_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (unsigned char) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static mrb_value
mrb_str_ord(mrb_state* mrb, mrb_value str)
{
  if (RSTRING_LEN(str) == 0)
    mrb_raise(mrb, E_ARGUMENT_ERROR, "empty string");
  return mrb_fixnum_value((unsigned char)RSTRING_PTR(str)[0]);
}