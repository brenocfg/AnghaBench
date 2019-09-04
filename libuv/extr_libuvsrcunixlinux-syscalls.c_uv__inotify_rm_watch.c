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
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int ENOSYS ; 
 int errno ; 

int uv__inotify_rm_watch(int fd, int32_t wd) {
#if defined(__NR_inotify_rm_watch)
  return syscall(__NR_inotify_rm_watch, fd, wd);
#else
  return errno = ENOSYS, -1;
#endif
}