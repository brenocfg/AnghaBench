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
 int ADF_ON ; 
 int /*<<< orphan*/  LEV_TARG_AD_OFF ; 
 int /*<<< orphan*/  ad_disable (struct advert*) ; 
 int /*<<< orphan*/  ad_is_ancient (int) ; 
 int /*<<< orphan*/  alloc_log_event (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int do_ad_disable (int ad_id) {
  struct advert *A = get_ad_f (ad_id, 0);
  if (!A && verbosity > 0 && !ad_is_ancient (ad_id)) {
    fprintf (stderr, "warning: disabling undefined ad %d\n", ad_id);
  }
  if (A && (A->flags & ADF_ON)) {
    alloc_log_event (LEV_TARG_AD_OFF, 8, ad_id);
    ad_disable (A);
    return 1;
  }
  return 0;
}