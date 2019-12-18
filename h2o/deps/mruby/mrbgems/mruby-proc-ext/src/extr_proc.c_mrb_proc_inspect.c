#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * irep; } ;
struct RProc {TYPE_1__ body; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  int /*<<< orphan*/  mrb_irep ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MRB_PROC_CFUNC_P (struct RProc*) ; 
 scalar_t__ MRB_PROC_STRICT_P (struct RProc*) ; 
 int /*<<< orphan*/  mrb_cptr (int /*<<< orphan*/ ) ; 
 char* mrb_debug_get_filename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mrb_debug_get_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_format (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct RProc* mrb_proc_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ptr_to_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat_cstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  mrb_str_cat_lit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_lit (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static mrb_value
mrb_proc_inspect(mrb_state *mrb, mrb_value self)
{
  struct RProc *p = mrb_proc_ptr(self);
  mrb_value str = mrb_str_new_lit(mrb, "#<Proc:");
  mrb_str_concat(mrb, str, mrb_ptr_to_str(mrb, mrb_cptr(self)));

  if (!MRB_PROC_CFUNC_P(p)) {
    mrb_irep *irep = p->body.irep;
    const char *filename;
    int32_t line;
    mrb_str_cat_lit(mrb, str, "@");

    filename = mrb_debug_get_filename(irep, 0);
    mrb_str_cat_cstr(mrb, str, filename ? filename : "-");
    mrb_str_cat_lit(mrb, str, ":");

    line = mrb_debug_get_line(irep, 0);
    if (line != -1) {
      str = mrb_format(mrb, "%S:%S", str, mrb_fixnum_value(line));
    }
    else {
      mrb_str_cat_lit(mrb, str, "-");
    }
  }

  if (MRB_PROC_STRICT_P(p)) {
    mrb_str_cat_lit(mrb, str, " (lambda)");
  }

  mrb_str_cat_lit(mrb, str, ">");
  return str;
}