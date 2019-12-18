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
 int /*<<< orphan*/ * filename_newidx ; 
 int* newidx_fd ; 
 int newidx_fds ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tszfree (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void snapshots_free (void) {
  int k;
  for (k = 0; k < newidx_fds; k++) {
    tszfree (filename_newidx[k], strlen (filename_newidx[k]) + 1);
    newidx_fd[k] = -1;
  }
}