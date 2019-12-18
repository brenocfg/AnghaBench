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
struct lev_generic {int a; int type; } ;
struct advert {scalar_t__ price; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADF_LIMIT_VIEWS ; 
 int /*<<< orphan*/  ad_is_ancient (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 scalar_t__ load_ancient_ad (struct advert*) ; 

__attribute__((used)) static int ad_limit_user_views (struct lev_generic *E) {
  int ad_id = E->a;
  int views = E->type & 0xffff;
  assert (!views || views == 100);
  struct advert *A = get_ad_f (ad_id, ad_is_ancient (ad_id));
  if (!A) { 
    return -1; 
  }

  assert (load_ancient_ad (A) >= 0);
  assert (A->price < 0);

  if (!views) {
    A->flags &= ~ADF_LIMIT_VIEWS;
  } else {
    A->flags |= ADF_LIMIT_VIEWS;
  }

  return 1;
}