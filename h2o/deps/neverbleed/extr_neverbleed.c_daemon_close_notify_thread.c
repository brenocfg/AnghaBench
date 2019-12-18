#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_6__ {TYPE_2__* nb; } ;
struct TYPE_4__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_5__ {TYPE_1__ sun_; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 TYPE_3__ daemon_vars ; 
 int /*<<< orphan*/  dirname (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  unlink_dir (int /*<<< orphan*/ ) ; 

__attribute__((used)) __attribute__((noreturn)) static void *daemon_close_notify_thread(void *_close_notify_fd)
{
    int close_notify_fd = (int)((char *)_close_notify_fd - (char *)NULL);
    char b;
    ssize_t r;

Redo:
    r = read(close_notify_fd, &b, 1);
    if (r == -1 && errno == EINTR)
        goto Redo;
    if (r > 0)
        goto Redo;
    /* close or error */

    /* unlink the temporary directory and socket file */
    unlink_dir(dirname(daemon_vars.nb->sun_.sun_path));

    _exit(0);
}