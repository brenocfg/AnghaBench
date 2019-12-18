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
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_wrlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_fd_lock ; 
 int /*<<< orphan*/  svc_fdset ; 

void
svc_exit(void)
{
	rwlock_wrlock(&svc_fd_lock);
	FD_ZERO(&svc_fdset);
	rwlock_unlock(&svc_fd_lock);
}