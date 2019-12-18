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
struct advert {int flags; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ADF_NEWANCIENT ; 
 int MAX_ADS ; 
 scalar_t__ ad_became_ancient (struct advert*) ; 
 scalar_t__ ad_is_ancient (int) ; 
 struct advert* get_ad (int) ; 
 int /*<<< orphan*/  new_fresh_ads ; 
 int new_stale_ads ; 

void mark_ancient_ads (void) {
  int i, j = 0;
  for (i = 0; i < MAX_ADS; i++) {
    struct advert *A = get_ad (i);
    if (A) {
      if (ad_became_ancient (A)) {
	A->flags |= ADF_NEWANCIENT;
	j++;
      } else {
	if (!(A->flags & ADF_ANCIENT)) {
	  ++new_fresh_ads;
	} else {
	  j++;
	}
      }
    } else if (ad_is_ancient (i)) {
      j++;
    }
  }
  new_stale_ads = j;
}