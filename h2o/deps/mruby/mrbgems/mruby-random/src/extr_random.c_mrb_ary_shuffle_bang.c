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
typedef  int /*<<< orphan*/  mt_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;
typedef  size_t mrb_int ;

/* Variables and functions */
 int RARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RARRAY_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_random_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_ary_modify (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_ary_ptr (int /*<<< orphan*/ ) ; 
 size_t mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_value (int) ; 
 int /*<<< orphan*/  mrb_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_random_mt_rand (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_random_rand_seed (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mt_state_type ; 

__attribute__((used)) static mrb_value
mrb_ary_shuffle_bang(mrb_state *mrb, mrb_value ary)
{
  mrb_int i;
  mt_state *random = NULL;

  if (RARRAY_LEN(ary) > 1) {
    mrb_get_args(mrb, "|d", &random, &mt_state_type);

    if (random == NULL) {
      random = get_random_state(mrb);
    }
    mrb_random_rand_seed(mrb, random);

    mrb_ary_modify(mrb, mrb_ary_ptr(ary));

    for (i = RARRAY_LEN(ary) - 1; i > 0; i--)  {
      mrb_int j;
      mrb_value *ptr = RARRAY_PTR(ary);
      mrb_value tmp;


      j = mrb_fixnum(mrb_random_mt_rand(mrb, random, mrb_fixnum_value(RARRAY_LEN(ary))));

      tmp = ptr[i];
      ptr[i] = ptr[j];
      ptr[j] = tmp;
    }
  }

  return ary;
}