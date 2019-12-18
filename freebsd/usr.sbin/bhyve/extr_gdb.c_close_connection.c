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
 int /*<<< orphan*/  cur_comm ; 
 int cur_fd ; 
 int /*<<< orphan*/  cur_resp ; 
 int /*<<< orphan*/  gdb_lock ; 
 int /*<<< orphan*/  gdb_resume_vcpus () ; 
 int /*<<< orphan*/  io_buffer_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mevent_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mevent_delete_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_event ; 
 int /*<<< orphan*/ * write_event ; 

__attribute__((used)) static void
close_connection(void)
{

	/*
	 * XXX: This triggers a warning because mevent does the close
	 * before the EV_DELETE.
	 */
	pthread_mutex_lock(&gdb_lock);
	mevent_delete(write_event);
	mevent_delete_close(read_event);
	write_event = NULL;
	read_event = NULL;
	io_buffer_reset(&cur_comm);
	io_buffer_reset(&cur_resp);
	cur_fd = -1;

	/* Resume any stopped vCPUs. */
	gdb_resume_vcpus();
	pthread_mutex_unlock(&gdb_lock);
}