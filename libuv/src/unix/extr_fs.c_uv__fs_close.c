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
 scalar_t__ EINPROGRESS ; 
 scalar_t__ EINTR ; 
 scalar_t__ errno ; 
 int uv__close_nocancel (int) ; 

__attribute__((used)) static int uv__fs_close(int fd) {
  int rc;

  rc = uv__close_nocancel(fd);
  if (rc == -1)
    if (errno == EINTR || errno == EINPROGRESS)
      rc = 0;  /* The close is in progress, not an error. */

  return rc;
}