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
 int /*<<< orphan*/  SAVE_ERRNO (int /*<<< orphan*/ ) ; 
 int STDERR_FILENO ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  epoll_file_close (int) ; 
 int uv__close_nocheckstdio (int) ; 

int uv__close(int fd) {
  assert(fd > STDERR_FILENO);  /* Catch stdio close bugs. */
#if defined(__MVS__)
  SAVE_ERRNO(epoll_file_close(fd));
#endif
  return uv__close_nocheckstdio(fd);
}