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
 int /*<<< orphan*/  mrb_gc_arena_restore (int /*<<< orphan*/ *,int) ; 
 int mrb_gc_arena_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_hash_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_str_new (int /*<<< orphan*/ *,char*,int) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

__attribute__((used)) static mrb_value
mrb_env_to_hash(mrb_state *mrb, mrb_value self)
{
  int i;
  mrb_value hash;

  hash = mrb_hash_new(mrb);
  for (i = 0; environ[i] != NULL; i++) {
    char *str = strchr(environ[i], '=');
    if (str != NULL) {
      mrb_value val;
      int ai = mrb_gc_arena_save(mrb);
      int len = str - environ[i];
      mrb_value key = mrb_str_new(mrb, environ[i], len);
      str++;
      val = mrb_str_new(mrb, str, strlen(str));
      mrb_hash_set(mrb, hash, key, val);
      mrb_gc_arena_restore(mrb, ai);
    }
  }

  return hash;
}