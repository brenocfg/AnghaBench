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
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  close (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 

__attribute__((used)) static int mpipe(int *fds) {
  if (pipe(fds) == -1)
    return -1;
  if (fcntl(fds[0], F_SETFD, FD_CLOEXEC) == -1 ||
      fcntl(fds[1], F_SETFD, FD_CLOEXEC) == -1) {
    close(fds[0]);
    close(fds[1]);
    return -1;
  }
  return 0;
}