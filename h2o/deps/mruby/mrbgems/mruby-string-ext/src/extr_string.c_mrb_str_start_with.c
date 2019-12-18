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
 int /*<<< orphan*/  RSTRING_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  mrb_ensure_string_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_false_value () ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,size_t*) ; 
 int /*<<< orphan*/  mrb_true_value () ; 

__attribute__((used)) static mrb_value
mrb_str_start_with(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv, sub;
  mrb_int argc, i;
  mrb_get_args(mrb, "*", &argv, &argc);

  for (i = 0; i < argc; i++) {
    size_t len_l, len_r;
    int ai = mrb_gc_arena_save(mrb);
    sub = mrb_ensure_string_type(mrb, argv[i]);
    mrb_gc_arena_restore(mrb, ai);
    len_l = RSTRING_LEN(self);
    len_r = RSTRING_LEN(sub);
    if (len_l >= len_r) {
      if (memcmp(RSTRING_PTR(self), RSTRING_PTR(sub), len_r) == 0) {
        return mrb_true_value();
      }
    }
  }
  return mrb_false_value();
}