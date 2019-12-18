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
typedef  int /*<<< orphan*/  optval ;
typedef  enum ev_type { ____Placeholder_ev_type } ev_type ;

/* Variables and functions */
 int /*<<< orphan*/  EVF_READ ; 
 int /*<<< orphan*/  EVF_WRITE ; 
 int /*<<< orphan*/  SOCK_NONBLOCK ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_NOSIGPIPE ; 
 int accept4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int cur_fd ; 
 scalar_t__ cur_vcpu ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int first_stop ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  gdb_readable ; 
 int /*<<< orphan*/  gdb_suspend_vcpus () ; 
 int /*<<< orphan*/  gdb_writable ; 
 void* mevent_add (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mevent_delete_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_event ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int stepping_vcpu ; 
 int stop_pending ; 
 int stopped_vcpu ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 
 int /*<<< orphan*/ * write_event ; 

__attribute__((used)) static void
new_connection(int fd, enum ev_type event, void *arg)
{
	int optval, s;

	s = accept4(fd, NULL, NULL, SOCK_NONBLOCK);
	if (s == -1) {
		if (arg != NULL)
			err(1, "Failed accepting initial GDB connection");

		/* Silently ignore errors post-startup. */
		return;
	}

	optval = 1;
	if (setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &optval, sizeof(optval)) ==
	    -1) {
		warn("Failed to disable SIGPIPE for GDB connection");
		close(s);
		return;
	}

	pthread_mutex_lock(&gdb_lock);
	if (cur_fd != -1) {
		close(s);
		warnx("Ignoring additional GDB connection.");
	}

	read_event = mevent_add(s, EVF_READ, gdb_readable, NULL);
	if (read_event == NULL) {
		if (arg != NULL)
			err(1, "Failed to setup initial GDB connection");
		pthread_mutex_unlock(&gdb_lock);
		return;
	}
	write_event = mevent_add(s, EVF_WRITE, gdb_writable, NULL);
	if (write_event == NULL) {
		if (arg != NULL)
			err(1, "Failed to setup initial GDB connection");
		mevent_delete_close(read_event);
		read_event = NULL;
	}

	cur_fd = s;
	cur_vcpu = 0;
	stepping_vcpu = -1;
	stopped_vcpu = -1;
	stop_pending = false;

	/* Break on attach. */
	first_stop = true;
	gdb_suspend_vcpus();
	pthread_mutex_unlock(&gdb_lock);
}