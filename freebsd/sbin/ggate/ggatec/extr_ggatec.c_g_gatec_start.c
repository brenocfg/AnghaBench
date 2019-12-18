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
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_gate_destroy (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  g_gate_xlog (char*,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_self () ; 
 scalar_t__ reconnect ; 
 int /*<<< orphan*/  recv_thread ; 
 int /*<<< orphan*/  recvfd ; 
 int /*<<< orphan*/  recvtd ; 
 int /*<<< orphan*/  send_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendfd ; 
 int /*<<< orphan*/  sendtd ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  unit ; 

__attribute__((used)) static void
g_gatec_start(void)
{
	int error;

	reconnect = 0;
	error = pthread_create(&recvtd, NULL, recv_thread, NULL);
	if (error != 0) {
		g_gate_destroy(unit, 1);
		g_gate_xlog("pthread_create(recv_thread): %s.",
		    strerror(error));
	}
	sendtd = pthread_self();
	send_thread(NULL);
	/* Disconnected. */
	close(sendfd);
	close(recvfd);
}