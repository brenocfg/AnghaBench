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
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_int ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  c; } ;

/* Variables and functions */
 scalar_t__ MRB_TT_FIXNUM ; 
 TYPE_1__* mrb_basic_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_class_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_const_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (scalar_t__) ; 
 int mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_hash_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_iv_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_module_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_nil_value () ; 
 int /*<<< orphan*/  mrb_obj_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_cat2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_str_new_cstr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ mrb_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static mrb_value
mrb_sce_init(mrb_state *mrb, mrb_value self)
{
  mrb_value c, e2c, m, str;
  mrb_int n;
  int argc, no_errno = 0;
  char buf[20];

  argc = mrb_get_args(mrb, "o|i", &m, &n);
  if (argc == 1) {
    if (mrb_type(m) == MRB_TT_FIXNUM) {
      n = mrb_fixnum(m);
      m = mrb_nil_value();
    } else {
      no_errno = 1;
    }
  }
  if (!no_errno) {
    e2c = mrb_const_get(mrb, mrb_obj_value(mrb_module_get(mrb, "Errno")), mrb_intern_lit(mrb, "Errno2class"));
    c = mrb_hash_fetch(mrb, e2c, mrb_fixnum_value(n), mrb_nil_value());
    if (!mrb_nil_p(c)) {
      mrb_basic_ptr(self)->c = mrb_class_ptr(c);
      str = mrb_str_new_cstr(mrb, strerror(n));
    } else {
      mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "errno"), mrb_fixnum_value(n));
      str = mrb_str_new_cstr(mrb, "Unknown error: ");
      snprintf(buf, sizeof(buf), "%d", (int)n);
      mrb_str_cat2(mrb, str, buf);
    }
  } else {
    str = mrb_str_new_cstr(mrb, "unknown error");
  }
  if (!mrb_nil_p(m)) {
    mrb_str_cat2(mrb, str, " - ");
    mrb_str_append(mrb, str, m);
  }
  mrb_iv_set(mrb, self, mrb_intern_lit(mrb, "mesg"), str);
  return self;
}