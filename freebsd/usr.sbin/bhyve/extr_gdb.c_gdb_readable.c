#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;
struct TYPE_5__ {int len; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_command (int) ; 
 int /*<<< orphan*/  close_connection () ; 
 TYPE_1__ cur_comm ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  gdb_lock ; 
 int io_buffer_avail (TYPE_1__*) ; 
 int /*<<< orphan*/  io_buffer_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  io_buffer_tail (TYPE_1__*) ; 
 int ioctl (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int read (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
gdb_readable(int fd, enum ev_type event, void *arg)
{
	ssize_t nread;
	int pending;

	if (ioctl(fd, FIONREAD, &pending) == -1) {
		warn("FIONREAD on GDB socket");
		return;
	}

	/*
	 * 'pending' might be zero due to EOF.  We need to call read
	 * with a non-zero length to detect EOF.
	 */
	if (pending == 0)
		pending = 1;

	/* Ensure there is room in the command buffer. */
	io_buffer_grow(&cur_comm, pending);
	assert(io_buffer_avail(&cur_comm) >= pending);

	nread = read(fd, io_buffer_tail(&cur_comm), io_buffer_avail(&cur_comm));
	if (nread == 0) {
		close_connection();
	} else if (nread == -1) {
		if (errno == EAGAIN)
			return;

		warn("Read from GDB socket");
		close_connection();
	} else {
		cur_comm.len += nread;
		pthread_mutex_lock(&gdb_lock);
		check_command(fd);
		pthread_mutex_unlock(&gdb_lock);
	}
}