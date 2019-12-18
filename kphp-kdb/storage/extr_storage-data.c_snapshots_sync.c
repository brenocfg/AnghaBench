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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/ * filename_newidx ; 
 scalar_t__ fsync (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int* newidx_fd ; 
 int newidx_fds ; 

__attribute__((used)) static int snapshots_sync (void) {
  int k, ok = 0;
  for (k = 0; k < newidx_fds; k++) {
    if (newidx_fd[k] >= 0) {
      if (fsync (newidx_fd[k]) < 0) {
        kprintf ("%s syncing fail. %m\n", filename_newidx[k]);
        close (newidx_fd[k]);
        newidx_fd[k] = -1;
      } else {
        ok++;
      }
    }
  }
  return ok;
}