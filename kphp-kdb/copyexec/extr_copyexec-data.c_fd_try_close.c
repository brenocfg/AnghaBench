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

__attribute__((used)) static int fd_try_close (int fd) {
  while (1) {
    if (close (fd) < 0) {
      if (errno == EINTR) {
        continue;
      }
      return 0;
    }
    return 1;
  }
}