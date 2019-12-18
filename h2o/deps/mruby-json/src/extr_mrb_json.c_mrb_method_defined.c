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
typedef  scalar_t__ mrb_sym ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;
typedef  int /*<<< orphan*/  mrb_bool ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 size_t RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ mrb_array_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_funcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 scalar_t__ mrb_intern_cstr (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ mrb_symbol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_bool
mrb_method_defined(mrb_state* mrb, mrb_value value, const char* name) {
  int ai = mrb_gc_arena_save(mrb);
  mrb_sym mid = mrb_intern_cstr(mrb, name);
  mrb_value methods = mrb_funcall(mrb, value, "public_methods", 1, mrb_false_value());
  mrb_bool included = FALSE;
  if (mrb_array_p(methods)) {
    mrb_int i;
    for (i = 0; i < RARRAY_LEN(methods); ++i) {
      if (mid == mrb_symbol(RARRAY_PTR(methods)[i])) {
        included = TRUE;
        break;
      }
    }
  }
  mrb_gc_arena_restore(mrb, ai);
  return included;
}