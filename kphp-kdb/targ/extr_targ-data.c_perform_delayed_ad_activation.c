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
struct advert {int flags; struct advert* hash_next; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ADF_DELAYED ; 
 int ADF_ON ; 
 long AD_TABLE_SIZE ; 
 struct advert** Ads ; 
 int /*<<< orphan*/  activate_ad (struct advert*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ delay_targeting ; 

int perform_delayed_ad_activation (void) {
  long i;
  int c = 0;
  delay_targeting = 0;
  for (i = 0; i < AD_TABLE_SIZE; i++) {
    struct advert *A;
    for (A = Ads[i]; A; A = A->hash_next) {
      if (A->flags & ADF_DELAYED) {
	assert ((A->flags & (ADF_ON | ADF_ANCIENT)) == ADF_ON);
	A->flags &= ~ADF_DELAYED;
	activate_ad (A);
	c++;
      }
    }
  }
  return c;
}