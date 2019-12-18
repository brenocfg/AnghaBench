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
 scalar_t__ EINTR ; 
 scalar_t__ close (int) ; 
 scalar_t__ errno ; 
 int fd_close_success_level ; 
 int /*<<< orphan*/  vkprintf (int,char*,int) ; 

__attribute__((used)) static void fd_close (int *fd) {
  if (*fd >= 0) {
    while (1) {
      if (close (*fd) < 0) {
        if (errno == EINTR) {
          continue;
        }
        vkprintf (2, "close (%d) failed. %m\n", *fd);
        return;
      }
      vkprintf (fd_close_success_level, "fd = %d: was successfully closed.\n", *fd);
      *fd = -1;
      return;
    }
  }
  vkprintf (3, "skip closing negative fd = %d\n", *fd);
}