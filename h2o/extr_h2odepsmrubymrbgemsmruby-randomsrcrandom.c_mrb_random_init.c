#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  seed; int /*<<< orphan*/  has_seed; scalar_t__ mti; } ;
typedef  TYPE_1__ mt_state ;
typedef  int /*<<< orphan*/  mrb_value ;
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 scalar_t__ DATA_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ N ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  get_opt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_data_init (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_fixnum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_fixnum_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ mrb_malloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ mrb_nil_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrb_random_mt_srand (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt_state_type ; 

__attribute__((used)) static mrb_value
mrb_random_init(mrb_state *mrb, mrb_value self)
{
  mrb_value seed;
  mt_state *t;

  seed = get_opt(mrb);

  /* avoid memory leaks */
  t = (mt_state*)DATA_PTR(self);
  if (t) {
    mrb_free(mrb, t);
  }
  mrb_data_init(self, NULL, &mt_state_type);

  t = (mt_state *)mrb_malloc(mrb, sizeof(mt_state));
  t->mti = N + 1;

  seed = mrb_random_mt_srand(mrb, t, seed);
  if (mrb_nil_p(seed)) {
    t->has_seed = FALSE;
  }
  else {
    mrb_assert(mrb_fixnum_p(seed));
    t->has_seed = TRUE;
    t->seed = mrb_fixnum(seed);
  }

  mrb_data_init(self, t, &mt_state_type);

  return self;
}