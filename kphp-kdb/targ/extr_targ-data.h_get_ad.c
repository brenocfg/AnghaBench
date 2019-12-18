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
struct advert {int ad_id; struct advert* hash_next; } ;

/* Variables and functions */
 int AD_TABLE_SIZE ; 
 struct advert** Ads ; 

__attribute__((used)) static inline struct advert *get_ad (int ad_id) {
  struct advert *A;
  for (A = Ads[ad_id & (AD_TABLE_SIZE - 1)]; A && A->ad_id != ad_id; A = A->hash_next);
  return A;
}