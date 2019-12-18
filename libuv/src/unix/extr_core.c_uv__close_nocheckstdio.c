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
 int EINPROGRESS ; 
 int UV_EINTR ; 
 int UV__ERR (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int uv__close_nocancel (int) ; 

int uv__close_nocheckstdio(int fd) {
  int saved_errno;
  int rc;

  assert(fd > -1);  /* Catch uninitialized io_watcher.fd bugs. */

  saved_errno = errno;
  rc = uv__close_nocancel(fd);
  if (rc == -1) {
    rc = UV__ERR(errno);
    if (rc == UV_EINTR || rc == UV__ERR(EINPROGRESS))
      rc = 0;    /* The close is in progress, not an error. */
    errno = saved_errno;
  }

  return rc;
}