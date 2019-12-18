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
struct ssh {int dummy; } ;
struct TYPE_2__ {scalar_t__ request_tty; } ;

/* Variables and functions */
 scalar_t__ REQUEST_TTY_FORCE ; 
 int /*<<< orphan*/  channel_cancel_cleanup (struct ssh*,int) ; 
 int /*<<< orphan*/  leave_raw_mode (int) ; 
 TYPE_1__ options ; 
 int session_closed ; 

__attribute__((used)) static void
client_channel_closed(struct ssh *ssh, int id, void *arg)
{
	channel_cancel_cleanup(ssh, id);
	session_closed = 1;
	leave_raw_mode(options.request_tty == REQUEST_TTY_FORCE);
}