#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_callback_t ;
struct TYPE_2__ {int /*<<< orphan*/  timer; } ;
struct fd {TYPE_1__ timerfd; } ;
typedef  scalar_t__ int_t ;
typedef  int /*<<< orphan*/  fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 scalar_t__ ITIMER_REAL_ ; 
 int /*<<< orphan*/  STRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _EINVAL ; 
 int /*<<< orphan*/  _ENOMEM ; 
 struct fd* adhoc_fd_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_install (struct fd*,scalar_t__) ; 
 int /*<<< orphan*/  timer_new (int /*<<< orphan*/ ,struct fd*) ; 
 scalar_t__ timerfd_callback ; 
 int /*<<< orphan*/  timerfd_ops ; 

fd_t sys_timerfd_create(int_t clockid, int_t flags) {
    STRACE("timerfd_create(%d, %#x)", clockid, flags);
    if (clockid != ITIMER_REAL_) {
        FIXME("timerfd %d", clockid);
        return _EINVAL;
    }

    struct fd *fd = adhoc_fd_create(&timerfd_ops);
    if (fd == NULL)
        return _ENOMEM;

    fd->timerfd.timer = timer_new((timer_callback_t) timerfd_callback, fd);
    return f_install(fd, flags);
}