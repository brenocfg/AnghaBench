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
struct fd {int real_fd; } ;
typedef  int /*<<< orphan*/  fd_t ;

/* Variables and functions */
 int /*<<< orphan*/  _ENOMEM ; 
 struct fd* adhoc_fd_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f_install (struct fd*,int) ; 
 int /*<<< orphan*/  realfs_fdops ; 

__attribute__((used)) static fd_t pipe_f_create(int pipe_fd, int flags) {
    struct fd *fd = adhoc_fd_create(&realfs_fdops);
    if (fd == NULL)
        return _ENOMEM;
    fd->real_fd = pipe_fd;
    return f_install(fd, flags);
}