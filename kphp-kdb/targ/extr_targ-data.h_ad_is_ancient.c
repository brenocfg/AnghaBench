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

/* Variables and functions */
 int* AncientAdBitmap ; 
 unsigned int MAX_ADS ; 

__attribute__((used)) static inline int ad_is_ancient (int ad_id) {
  return (unsigned) ad_id < MAX_ADS ? (AncientAdBitmap[ad_id >> 3] >> (ad_id & 7)) & 1 : 0;
}