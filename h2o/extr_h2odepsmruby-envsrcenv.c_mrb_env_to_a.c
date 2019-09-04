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
 char** environ ; 
 int /*<<< orphan*/  mrb_ary_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static mrb_value
mrb_env_to_a(mrb_state *mrb, mrb_value self)
{
  int i;
  mrb_value ary;

  ary = mrb_ary_new(mrb);
  for (i = 0; environ[i] != NULL; i++) {
    char *str = strchr(environ[i], '=');
    if (str != NULL) {
      int ai = mrb_gc_arena_save(mrb);
      mrb_value elem = mrb_ary_new(mrb);
      int len = str - environ[i];
      mrb_ary_push(mrb, elem, mrb_str_new(mrb, environ[i], len));
      str++;
      mrb_ary_push(mrb, elem, mrb_str_new(mrb, str, strlen(str)));
      mrb_ary_push(mrb, ary, elem);
      mrb_gc_arena_restore(mrb, ai);
    }
  }

  return ary;
}