#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct advert {scalar_t__ disabled_since; int flags; scalar_t__ userlist_computed_at; scalar_t__ user_list; scalar_t__ users; int /*<<< orphan*/  ad_id; } ;
struct TYPE_4__ {struct advert* first; TYPE_1__* last; } ;
struct TYPE_3__ {int /*<<< orphan*/  ad_id; } ;

/* Variables and functions */
 int ADF_ON ; 
 scalar_t__ AD_ANCIENT_DELAY ; 
 TYPE_2__ AHd_lru ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 scalar_t__ log_last_ts ; 
 int /*<<< orphan*/  remove_queue_ad (struct advert*) ; 
 int /*<<< orphan*/  tot_userlists ; 
 int /*<<< orphan*/  tot_userlists_size ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,struct advert*,...) ; 

int process_lru_ads (void) {
  int res = 0;
  vkprintf (3, "process_lru_ads() first=%d last=%d\n", AHd_lru.first->ad_id, AHd_lru.last->ad_id);
  while (AHd_lru.first != (struct advert *) &AHd_lru && AHd_lru.first->disabled_since <= log_last_ts - AD_ANCIENT_DELAY) {
    struct advert *A = AHd_lru.first;
    vkprintf (3, "first ad in lru queue: ad #%d (%p), disabled_since=%d, log_last_ts=%d\n", A->ad_id, A, A->disabled_since, log_last_ts);
    remove_queue_ad (A);
    assert (!(A->flags & ADF_ON));
    if (A->user_list) {
      tot_userlists--;
      tot_userlists_size -= A->users; 
      free (A->user_list);
      A->user_list = 0;
      A->userlist_computed_at = 0;
    }
    ++res;
  }
  return res;
}