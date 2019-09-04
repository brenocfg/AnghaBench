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
 int /*<<< orphan*/ * VD ; 
 int VN ; 
 scalar_t__ cmp_voting (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void kill_dup_votings (void) {
  int i, j = 1;
  if (!VN) {
    return;
  }
  for (i = 1; i < VN; i++) {
    if (cmp_voting (&VD[i-1], &VD[i])) {
      VD[j++] = VD[i];
    }
  }
  if (verbosity > 0) {
    fprintf (stderr, "deleted %d duplicate records\n", VN - j);
  }
  VN = j;
}