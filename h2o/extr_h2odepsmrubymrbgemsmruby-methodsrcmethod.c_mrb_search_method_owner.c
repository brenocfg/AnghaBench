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
struct RProc {int dummy; } ;
struct RClass {scalar_t__ tt; struct RClass* c; } ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  scalar_t__ mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  E_NAME_ERROR ; 
 scalar_t__ MRB_TT_ICLASS ; 
 struct RProc* method_search_vm (int /*<<< orphan*/ *,struct RClass**,int /*<<< orphan*/ ) ; 
 char* mrb_class_name (int /*<<< orphan*/ *,struct RClass*) ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_intern_lit (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mrb_raisef (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_respond_to (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new_static (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_sym2str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_symbol_value (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_test (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_true_value () ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
mrb_search_method_owner(mrb_state *mrb, struct RClass *c, mrb_value obj, mrb_sym name, struct RClass **owner, struct RProc **proc, mrb_bool unbound)
{
  mrb_value ret;
  const char *s;

  *owner = c;
  *proc = method_search_vm(mrb, owner, name);
  if (!*proc) {
    if (unbound) {
      goto name_error;
    }
    if (!mrb_respond_to(mrb, obj, mrb_intern_lit(mrb, "respond_to_missing?"))) {
      goto name_error;
    }
    ret = mrb_funcall(mrb, obj, "respond_to_missing?", 2, mrb_symbol_value(name), mrb_true_value());
    if (!mrb_test(ret)) {
      goto name_error;
    }
    *owner = c;
  }

  while ((*owner)->tt == MRB_TT_ICLASS)
    *owner = (*owner)->c;

  return;

name_error:
  s = mrb_class_name(mrb, c);
  mrb_raisef(
    mrb, E_NAME_ERROR,
    "undefined method `%S' for class `%S'",
    mrb_sym2str(mrb, name),
    mrb_str_new_static(mrb, s, strlen(s))
  );
}