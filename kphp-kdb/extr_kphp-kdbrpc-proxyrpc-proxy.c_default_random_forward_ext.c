#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tot_buckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 int /*<<< orphan*/  assert (int) ; 
 int lrand48 () ; 
 int query_forward (int /*<<< orphan*/ ) ; 
 scalar_t__ tl_fetch_error () ; 
 int /*<<< orphan*/  tl_fetch_mark_delete () ; 
 int /*<<< orphan*/  tl_fetch_mark_restore () ; 

int default_random_forward_ext (void) {
  int n = lrand48 ();
  if (tl_fetch_error ()) {
    tl_fetch_mark_delete ();
    return -1;
  }
  assert (CC->tot_buckets);
  assert (n >= 0);
  n %= CC->tot_buckets;
  tl_fetch_mark_restore ();
  return query_forward (CC->buckets[n]);
}