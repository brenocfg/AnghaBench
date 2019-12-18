#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_connection () ; 
 TYPE_1__ cur_resp ; 
 int /*<<< orphan*/  io_buffer_advance (TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_buffer_head (TYPE_1__*) ; 
 int /*<<< orphan*/  mevent_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mevent_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int write (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_event ; 

__attribute__((used)) static void
send_pending_data(int fd)
{
	ssize_t nwritten;

	if (cur_resp.len == 0) {
		mevent_disable(write_event);
		return;
	}
	nwritten = write(fd, io_buffer_head(&cur_resp), cur_resp.len);
	if (nwritten == -1) {
		warn("Write to GDB socket failed");
		close_connection();
	} else {
		io_buffer_advance(&cur_resp, nwritten);
		if (cur_resp.len == 0)
			mevent_disable(write_event);
		else
			mevent_enable(write_event);
	}
}