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
struct TYPE_2__ {int cluster_mode; int step; int tot_buckets; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 TYPE_1__* CC ; 
 int /*<<< orphan*/  assert (int) ; 
 int query_forward (int /*<<< orphan*/ ) ; 
 scalar_t__ tl_fetch_error () ; 
 int tl_fetch_int () ; 
 int /*<<< orphan*/  tl_fetch_mark_delete () ; 
 int /*<<< orphan*/  tl_fetch_mark_restore () ; 

int default_vector_forward_ext (void) {
  tl_fetch_int (); //op
  int x = (CC->cluster_mode & 7);
  x --;
  if (x < 0) { x = 0; }
  int n = tl_fetch_int (); // n
  if (x > n - 1) { x = n - 1; }
  int i;
  for (i = 0; i < x; i++) {
    tl_fetch_int ();
  }
  n = tl_fetch_int ();
  if (n < 0) { n = -n; }
  if (n < 0) { n = 0; }
  if (tl_fetch_error ()) {
    tl_fetch_mark_delete ();
    return -1;
  }
  if (CC->step) {
    n /= CC->step;
  }
  assert (CC->tot_buckets);
  n %= CC->tot_buckets;
  tl_fetch_mark_restore ();
  return query_forward (CC->buckets[n]);
}