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
 scalar_t__ MRB_TT_STRING ; 
 scalar_t__ RSTRING_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_cstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_type (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mrb_io_read_data_pending(mrb_state *mrb, mrb_value io)
{
  mrb_value buf = mrb_iv_get(mrb, io, mrb_intern_cstr(mrb, "@buf"));
  if (mrb_type(buf) == MRB_TT_STRING && RSTRING_LEN(buf) > 0) {
    return 1;
  }
  return 0;
}