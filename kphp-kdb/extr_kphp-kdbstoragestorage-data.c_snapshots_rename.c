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
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ) ; 
 int* newidx_fd ; 
 int newidx_fds ; 
 scalar_t__ rename_temporary_snapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snapshots_rename (void) {
  int k, ok = 0;
  for (k = 0; k < newidx_fds; k++) {
    if (newidx_fd[k] >= 0) {
      if (rename_temporary_snapshot (filename_newidx[k])) {
        kprintf ("cannot rename new index file from %s: %m\n", filename_newidx[k]);
        unlink (filename_newidx[k]);
        newidx_fd[k] = -1;
      } else {
        ok++;
      }
    }
  }
  return ok;
}