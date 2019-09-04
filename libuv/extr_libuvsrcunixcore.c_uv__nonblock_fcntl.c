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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int UV__ERR (scalar_t__) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

int uv__nonblock_fcntl(int fd, int set) {
  int flags;
  int r;

  do
    r = fcntl(fd, F_GETFL);
  while (r == -1 && errno == EINTR);

  if (r == -1)
    return UV__ERR(errno);

  /* Bail out now if already set/clear. */
  if (!!(r & O_NONBLOCK) == !!set)
    return 0;

  if (set)
    flags = r | O_NONBLOCK;
  else
    flags = r & ~O_NONBLOCK;

  do
    r = fcntl(fd, F_SETFL, flags);
  while (r == -1 && errno == EINTR);

  if (r)
    return UV__ERR(errno);

  return 0;
}