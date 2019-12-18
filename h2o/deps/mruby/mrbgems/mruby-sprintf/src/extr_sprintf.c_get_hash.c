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
typedef  int mrb_int ;

/* Variables and functions */
 int /*<<< orphan*/  E_ARGUMENT_ERROR ; 
 int /*<<< orphan*/  mrb_check_hash_type (int /*<<< orphan*/ *,int /*<<< orphan*/  const) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_raise (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mrb_undef_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static mrb_value
get_hash(mrb_state *mrb, mrb_value *hash, mrb_int argc, const mrb_value *argv)
{
  mrb_value tmp;

  if (!mrb_undef_p(*hash)) return *hash;
  if (argc != 2) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "one hash required");
  }
  tmp = mrb_check_hash_type(mrb, argv[1]);
  if (mrb_nil_p(tmp)) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "one hash required");
  }
  return (*hash = tmp);
}