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
struct advert {int flags; int ad_id; int users; int /*<<< orphan*/  disabled_since; } ;

/* Variables and functions */
 int ADF_ANCIENT ; 
 int ADF_DELAYED ; 
 int ADF_ON ; 
 int /*<<< orphan*/  active_ads ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  deactivate_ad (struct advert*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  now ; 
 int /*<<< orphan*/  process_lru_ads () ; 
 int /*<<< orphan*/  reinsert_lru_ad_last (struct advert*) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

__attribute__((used)) static int ad_disable (struct advert *A) {
  if (!A) { 
    return 0; 
  }
  if (!(A->flags & ADF_ON)) { 
    return 1; 
  }
  assert (!(A->flags & ADF_ANCIENT));

  A->flags &= ~ADF_ON;
  active_ads--;
  A->disabled_since = now;

  if (!(A->flags & ADF_DELAYED)) {
    deactivate_ad (A);
  } else {
    A->flags &= ~ADF_DELAYED;
  }

  if (verbosity > 2) {
    fprintf (stderr, "disabled previously enabled ad #%d: %d users\n", A->ad_id, A->users);
  }

  reinsert_lru_ad_last (A);
  process_lru_ads ();

  return 1;
}