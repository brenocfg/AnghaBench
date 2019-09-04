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
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ lseek (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int* newidx_fd ; 
 int newidx_fds ; 

__attribute__((used)) static int snapshots_lseek (off_t offset) {
  int k, ok = 0;
  for (k = 0; k < newidx_fds; k++) {
    if (newidx_fd[k] >= 0 && lseek (newidx_fd[k], offset, SEEK_SET) == offset) {
      ok++;
    } else {
      if (newidx_fd[k] >= 0) {
        close (newidx_fd[k]);
        newidx_fd[k] = -1;
      }
    }
  }
  return ok;
}