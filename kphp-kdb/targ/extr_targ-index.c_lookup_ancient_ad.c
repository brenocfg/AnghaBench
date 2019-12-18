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
struct targ_index_ads_directory_entry {int ad_id; } ;

/* Variables and functions */
 struct targ_index_ads_directory_entry* idx_stale_ad_dir ; 
 int idx_stale_ads ; 

struct targ_index_ads_directory_entry *lookup_ancient_ad (int ad_id) {
  int a = -1, b = idx_stale_ads, c;
  while (b - a > 1) {
    c = (a + b) >> 1;
    if (idx_stale_ad_dir[c].ad_id <= ad_id) {
      a = c;
    } else {
      b = c;
    }
  }
  if (a >= 0 && idx_stale_ad_dir[a].ad_id == ad_id) {
    return &idx_stale_ad_dir[a];
  } else {
    return 0;
  }
}