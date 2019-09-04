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
struct lev_targ_ad_setint {int value; } ;
struct advert {int group; } ;

/* Variables and functions */
 int /*<<< orphan*/  LEV_TARG_AD_SETGROUP ; 
 int /*<<< orphan*/  ad_is_ancient (int) ; 
 int ad_set_group (struct lev_targ_ad_setint*) ; 
 struct lev_targ_ad_setint* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int load_ancient_ad (struct advert*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int do_ad_set_group (int ad_id, int group) {
  struct advert *A = get_ad_f (ad_id, ad_is_ancient (ad_id));

  if (verbosity > 0) {
    fprintf (stderr, "in do_ad_set_group (%d, %d):\n", ad_id, group);
  }

  if (!A || group == (-1 << 31)) {
    return 0;
  }

  int res = load_ancient_ad (A);
  if (res < 0) {
    return res;
  }

  if (A->group == group) {
    return 1;
  }

  struct lev_targ_ad_setint *E = alloc_log_event (LEV_TARG_AD_SETGROUP, 12, ad_id);
  E->value = group;

  return ad_set_group (E);
}