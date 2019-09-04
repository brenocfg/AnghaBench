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
struct lev_targ_ad_setint {int value; int /*<<< orphan*/  ad_id; } ;
struct advert {int factor; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_is_ancient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct advert* get_ad_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ load_ancient_ad (struct advert*) ; 

__attribute__((used)) static int ad_set_factor (struct lev_targ_ad_setint *E) {
  assert (E->value >= 0 && E->value <= 1000000);
  struct advert *A = get_ad_f (E->ad_id, ad_is_ancient (E->ad_id));
  if (!A) { 
    return -1; 
  }

  assert (load_ancient_ad (A) >= 0);

  A->factor = E->value * 1e-6;

  return 1;
}