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
 int /*<<< orphan*/  assert (int) ; 
 int engineN ; 
 int /*<<< orphan*/  max_user_events ; 
 int uf ; 
 int userN ; 
 int /*<<< orphan*/ * v ; 
 int /*<<< orphan*/  vct_add_lim (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void gen_events (int *a, int n) {
  int i, j;
  int mask = (1 << 30) - 1;
  for (i = 0; i < n; i++) {
    int can = 1, ida = a[i], idb;
    if (ida < 0) {
      ida = -ida;
    }

    if (ida > (1 << 30)) {
      can = 0;
      ida &= mask;
    }

    if (ida % engineN != uf) {
      continue;
    }
    assert (ida < userN);

    for (j = 0; j < n/* && events_left[ida] > 0*/; j++) {
      if (i != j) {
        //fprintf (stderr, "%d %d\n", a[i], a[j]);
        idb = a[j];
        if (idb < 0) {
          continue;
        }
        assert (idb < userN);
        //events_left[ida]--;

        idb &= mask;

        vct_add_lim (&v[ida / engineN], 2 * idb + can, max_user_events);
      }
    }
  }
}