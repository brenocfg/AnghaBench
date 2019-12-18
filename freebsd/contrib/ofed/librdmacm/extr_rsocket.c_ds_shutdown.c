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
struct rsocket {int opts; int fd_flags; int state; } ;

/* Variables and functions */
 int O_NONBLOCK ; 
 int RS_OPT_SVC_ACTIVE ; 
 int /*<<< orphan*/  RS_SVC_REM_DGRAM ; 
 int /*<<< orphan*/  ds_all_sends_done ; 
 int /*<<< orphan*/  ds_process_cqs (struct rsocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rs_notify_svc (int /*<<< orphan*/ *,struct rsocket*,int /*<<< orphan*/ ) ; 
 int rs_readable ; 
 int /*<<< orphan*/  rs_set_nonblocking (struct rsocket*,int) ; 
 int rs_writable ; 
 int /*<<< orphan*/  udp_svc ; 

__attribute__((used)) static void ds_shutdown(struct rsocket *rs)
{
	if (rs->opts & RS_OPT_SVC_ACTIVE)
		rs_notify_svc(&udp_svc, rs, RS_SVC_REM_DGRAM);

	if (rs->fd_flags & O_NONBLOCK)
		rs_set_nonblocking(rs, 0);

	rs->state &= ~(rs_readable | rs_writable);
	ds_process_cqs(rs, 0, ds_all_sends_done);

	if (rs->fd_flags & O_NONBLOCK)
		rs_set_nonblocking(rs, rs->fd_flags);
}