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
 int ENOSYS ; 
 int errno ; 

int uv__pipe2(int pipefd[2], int flags) {
#if defined(__NR_pipe2)
  int result;
  result = syscall(__NR_pipe2, pipefd, flags);
#if MSAN_ACTIVE
  if (!result)
    __msan_unpoison(pipefd, sizeof(int[2]));
#endif
  return result;
#else
  return errno = ENOSYS, -1;
#endif
}