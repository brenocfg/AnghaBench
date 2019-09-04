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
struct advert {int recent_views_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad_is_ancient (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 scalar_t__ load_ancient_ad (struct advert*) ; 

__attribute__((used)) static int ad_limit_recent_views (struct lev_generic *E) {
  int ad_id = E->a;
  int views = E->type & 0xffff;
  struct advert *A = get_ad_f (ad_id, ad_is_ancient (ad_id));
  if (!A) { 
    return -1; 
  }

  assert (load_ancient_ad (A) >= 0);

  A->recent_views_limit = views;

  return 1;
}