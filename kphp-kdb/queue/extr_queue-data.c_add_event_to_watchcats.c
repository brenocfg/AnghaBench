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
 int /*<<< orphan*/  add_event (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_watchcat_s (long long) ; 
 int my_verbosity ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 

void add_event_to_watchcats (long long *ids, int idn, char *event) {
  int len = strlen (event), i;

  if (my_verbosity > 1) {
    fprintf (stderr, "add %s to ", event);
  }
  for (i = 0; i < idn; i++) {
    if (my_verbosity > 1) {
      fprintf (stderr, " %lld", ids[i]);
    }
    add_event (get_queue (get_watchcat_s (ids[i]), 0), event, len, 0, 0, 0);
  }
  if (my_verbosity > 1) {
    fprintf (stderr, "\n");
  }
}