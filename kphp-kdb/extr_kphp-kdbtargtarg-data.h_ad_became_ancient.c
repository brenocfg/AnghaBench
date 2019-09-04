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
struct advert {int flags; scalar_t__ disabled_since; } ;

/* Variables and functions */
 int ADF_ON ; 
 scalar_t__ AD_ANCIENT_DELAY ; 
 scalar_t__ log_last_ts ; 

__attribute__((used)) static inline int ad_became_ancient (struct advert *A) {
  return !(A->flags & ADF_ON) && A->disabled_since <= log_last_ts - AD_ANCIENT_DELAY;
}