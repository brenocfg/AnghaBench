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
struct targ_index_ads_directory_entry {int ad_id; int ad_info_offset; } ;
struct advert {int flags; int ad_id; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ADF_NEWANCIENT ; 
 int MAX_ADS ; 
 struct targ_index_ads_directory_entry* NewStaleAdsDir ; 
 scalar_t__ ad_is_ancient (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 struct advert* get_ad (int) ; 
 struct targ_index_ads_directory_entry* malloc (int) ; 
 int new_stale_addir_size ; 
 int new_stale_ads ; 

void init_new_stale_ads_directory (void) {
  int i;
  new_stale_addir_size = sizeof (struct targ_index_ads_directory_entry) * (new_stale_ads + 1);
  struct targ_index_ads_directory_entry *p = NewStaleAdsDir = malloc (new_stale_addir_size);
  for (i = 0; i < MAX_ADS; i++) {
    struct advert *A = get_ad (i);
    if (A && (A->flags & (ADF_ANCIENT | ADF_NEWANCIENT))) {
      assert (p - NewStaleAdsDir < new_stale_ads);
      p->ad_id = A->ad_id;
      p->ad_info_offset = -1;
      ++p;
    } else if (ad_is_ancient (i)) {
      assert (!A);
      p->ad_id = i;
      p->ad_info_offset = -1;
      ++p;
    }
  }
  assert (p - NewStaleAdsDir == new_stale_ads);
  p->ad_id = 0x7fffffff;
  p->ad_info_offset = -1;
}