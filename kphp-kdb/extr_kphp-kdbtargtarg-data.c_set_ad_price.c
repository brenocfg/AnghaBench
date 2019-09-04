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
struct lev_targ_ad_price {scalar_t__ ad_price; int /*<<< orphan*/  ad_id; } ;
struct advert {scalar_t__ price; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_is_ancient (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compute_estimated_gain (struct advert*) ; 
 struct advert* get_ad_f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_ancient_ad (struct advert*) ; 

__attribute__((used)) static int set_ad_price (struct lev_targ_ad_price *E) {
  if (!E->ad_price) {
    return 0;
  }
  struct advert *A = get_ad_f (E->ad_id, ad_is_ancient (E->ad_id));
  if (!A) {
    return 0;
  }
  /* have to load this ancient ad */
  int res = load_ancient_ad (A);
  if (res < 0) {
    return res;
  }
    
  A->price = E->ad_price;  
  compute_estimated_gain (A);
  return 1;
}