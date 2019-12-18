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
struct lev_targ_ad_price {int ad_price; } ;
struct advert {int price; int flags; } ;

/* Variables and functions */
 int ADF_ON ; 
 int /*<<< orphan*/  LEV_TARG_AD_ON ; 
 int /*<<< orphan*/  LEV_TARG_AD_PRICE ; 
 int /*<<< orphan*/  ad_enable (struct advert*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ad_is_ancient (int) ; 
 struct lev_targ_ad_price* alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int load_ancient_ad (struct advert*) ; 
 int /*<<< orphan*/  set_ad_price (struct lev_targ_ad_price*) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int do_ad_price_enable (int ad_id, int price) {
  struct advert *A = get_ad_f (ad_id, ad_is_ancient (ad_id));
  int res;
  if (!A) {
    if (verbosity > 0) {
      fprintf (stderr, "warning: enabling undefined ad %d\n", ad_id);
    }
    return 0;
  }
  res = load_ancient_ad (A);
  if (res < 0) {
    return res;
  }
  res = 0;
  if (price != 0 && A->price != price) {
    struct lev_targ_ad_price *E = alloc_log_event (LEV_TARG_AD_PRICE, 12, ad_id);
    E->ad_price = price;
    set_ad_price (E);
    res = 1; 
  }
  if (!(A->flags & ADF_ON)) {
    alloc_log_event (LEV_TARG_AD_ON, 8, ad_id);
    ad_enable (A, 0);
    res |= 1;
  }
  return res;
}