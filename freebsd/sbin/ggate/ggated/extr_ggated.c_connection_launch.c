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
struct ggd_connection {int /*<<< orphan*/  c_path; } ;
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  disk_thread (struct ggd_connection*) ; 
 int errno ; 
 int fork () ; 
 int /*<<< orphan*/  g_gate_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_xlog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inqueue_cond ; 
 int /*<<< orphan*/  inqueue_mtx ; 
 int /*<<< orphan*/  outqueue_cond ; 
 int /*<<< orphan*/  outqueue_mtx ; 
 int pthread_cond_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ggd_connection*) ; 
 int pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  recv_thread ; 
 int /*<<< orphan*/  send_thread ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static void
connection_launch(struct ggd_connection *conn)
{
	pthread_t td;
	int error, pid;

	pid = fork();
	if (pid > 0)
		return;
	else if (pid == -1) {
		g_gate_log(LOG_ERR, "Cannot fork: %s.", strerror(errno));
		return;
	}
	g_gate_log(LOG_DEBUG, "Process created [%s].", conn->c_path);

	/*
	 * Create condition variables and mutexes for in-queue and out-queue
	 * synchronization.
	 */
	error = pthread_mutex_init(&inqueue_mtx, NULL);
	if (error != 0) {
		g_gate_xlog("pthread_mutex_init(inqueue_mtx): %s.",
		    strerror(error));
	}
	error = pthread_cond_init(&inqueue_cond, NULL);
	if (error != 0) {
		g_gate_xlog("pthread_cond_init(inqueue_cond): %s.",
		    strerror(error));
	}
	error = pthread_mutex_init(&outqueue_mtx, NULL);
	if (error != 0) {
		g_gate_xlog("pthread_mutex_init(outqueue_mtx): %s.",
		    strerror(error));
	}
	error = pthread_cond_init(&outqueue_cond, NULL);
	if (error != 0) {
		g_gate_xlog("pthread_cond_init(outqueue_cond): %s.",
		    strerror(error));
	}

	/*
	 * Create threads:
	 * recvtd - thread for receiving I/O request
	 * diskio - thread for doing I/O request
	 * sendtd - thread for sending I/O requests back
	 */
	error = pthread_create(&td, NULL, send_thread, conn);
	if (error != 0) {
		g_gate_xlog("pthread_create(send_thread): %s.",
		    strerror(error));
	}
	error = pthread_create(&td, NULL, recv_thread, conn);
	if (error != 0) {
		g_gate_xlog("pthread_create(recv_thread): %s.",
		    strerror(error));
	}
	disk_thread(conn);
}