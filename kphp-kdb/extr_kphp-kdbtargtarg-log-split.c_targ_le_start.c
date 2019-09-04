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
struct lev_start {scalar_t__ schema_id; scalar_t__ split_min; scalar_t__ split_max; int split_mod; } ;

/* Variables and functions */
 scalar_t__ TARG_SCHEMA_V1 ; 
 int /*<<< orphan*/  assert (int) ; 
 int copy_mod ; 
 int copy_rem ; 
 scalar_t__ split_max ; 
 scalar_t__ split_min ; 
 int split_mod ; 
 int split_quotient ; 
 int split_shift ; 

__attribute__((used)) static int targ_le_start (struct lev_start *E) {
  if (E->schema_id != TARG_SCHEMA_V1) {
    return -1;
  }
  if (split_mod) {
    return 0;
//    assert (E->split_mod >= split_mod && !(E->split_mod % split_mod) && split_min == E->split_min % split_mod && E->split_max == E->split_min + 1);
  }
  split_min = E->split_min;
  split_max = E->split_max;
  split_mod = E->split_mod;
  assert (split_mod > 0 && split_min >= 0 && split_min + 1 == split_max && split_max <= split_mod);
  if (split_quotient) {
    assert (copy_mod / split_quotient % split_mod == 0);
  } else {
    assert (copy_mod % split_mod == 0);
    split_quotient = copy_mod / split_mod;
  }
  split_shift = copy_rem / (copy_mod / split_quotient);

  return 0;
}