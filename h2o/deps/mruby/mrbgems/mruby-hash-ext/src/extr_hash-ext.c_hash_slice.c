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
typedef  scalar_t__ mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  mrb_hash_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_hash_new_capa (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mrb_hash_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_undef_value () ; 

__attribute__((used)) static mrb_value
hash_slice(mrb_state *mrb, mrb_value hash)
{
  mrb_value *argv, result;
  mrb_int argc, i;

  mrb_get_args(mrb, "*", &argv, &argc);
  if (argc == 0) {
    return mrb_hash_new_capa(mrb, argc);
  }
  result = mrb_hash_new_capa(mrb, argc);
  for (i = 0; i < argc; i++) {
    mrb_value key = argv[i];
    mrb_value val;

    val = mrb_hash_fetch(mrb, hash, key, mrb_undef_value());
    if (!mrb_undef_p(val)) {
      mrb_hash_set(mrb, result, key, val);
    }
  }
  return result;
}