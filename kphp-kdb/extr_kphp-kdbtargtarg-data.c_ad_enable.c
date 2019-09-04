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
struct advert {int flags; scalar_t__ disabled_since; int price; scalar_t__ userlist_computed_at; int ad_id; int users; int /*<<< orphan*/  user_list; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ADF_DELAYED ; 
 int ADF_ON ; 
 scalar_t__ AD_ANCIENT_DELAY ; 
 scalar_t__ AD_RECOMPUTE_INTERVAL ; 
 int /*<<< orphan*/  activate_ad (struct advert*) ; 
 int /*<<< orphan*/  active_ads ; 
 int /*<<< orphan*/  apply_periodic_ad_state (struct advert*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  change_ad_target (struct advert*) ; 
 int /*<<< orphan*/  compute_ad_user_list (struct advert*) ; 
 int /*<<< orphan*/  compute_estimated_gain (struct advert*) ; 
 int /*<<< orphan*/  delay_targeting ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int load_ancient_ad (struct advert*) ; 
 scalar_t__ log_last_ts ; 
 int /*<<< orphan*/  remove_queue_ad (struct advert*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static int ad_enable (struct advert *A, int price) {
  if (!A) { 
    return 0; 
  }
  if (A->flags & ADF_ANCIENT) {
    int res = load_ancient_ad (A);
    if (res < 0) {
      return res;
    }
    assert (A->disabled_since <= log_last_ts - AD_ANCIENT_DELAY);
  }

  if (price) {
    A->price = price;
  }

  assert (A->price);
  
  if (A->flags & ADF_ON) {
    if (A->userlist_computed_at <= log_last_ts - AD_RECOMPUTE_INTERVAL) {
      change_ad_target (A);
    } else {
      compute_estimated_gain (A);
    }
    return 0; 
  }

  if (!A->user_list || A->disabled_since <= log_last_ts - AD_ANCIENT_DELAY || A->userlist_computed_at <= log_last_ts - AD_RECOMPUTE_INTERVAL) {
    compute_ad_user_list (A);
  }

  remove_queue_ad (A);
  A->flags |= ADF_ON;
  active_ads++;

  if (!delay_targeting) {
    activate_ad (A);
  } else {
    A->flags |= ADF_DELAYED;
  }

  apply_periodic_ad_state (A);
  compute_estimated_gain (A);

  if (verbosity > 2) {
    fprintf (stderr, "enabled previously disabled ad #%d: %d users\n", A->ad_id, A->users);
  }

  return 1;
}