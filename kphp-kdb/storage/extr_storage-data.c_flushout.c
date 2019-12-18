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
 scalar_t__ io_buff ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int,int) ; 
 int* newidx_fd ; 
 int newidx_fds ; 
 scalar_t__ rptr ; 
 scalar_t__ wptr ; 
 int write (int,scalar_t__,int) ; 

__attribute__((used)) static void flushout (void) {
  int w, s;
  if (rptr < wptr) {
    int i;
    s = wptr - rptr;
    for (i = 0; i < newidx_fds; i++) {
      if (newidx_fd[i] >= 0) {
        w = write (newidx_fd[i], rptr, s);
        if (w != s) {
          kprintf ("Write to %s failed (%d of %d) bytes written. %m\n" , filename_newidx[i], w, s);
          close (newidx_fd[i]);
          newidx_fd[i] = -1;
        }
      }
    }
  }
  rptr = wptr = io_buff;
}