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
 int EBUSY ; 
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listen_start_eh ; 
 int /*<<< orphan*/  listen_stop_eh ; 
 int /*<<< orphan*/  lle_event ; 
 int /*<<< orphan*/  lle_event_eh ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_offload_listen_start ; 
 int /*<<< orphan*/  tcp_offload_listen_stop ; 
 int /*<<< orphan*/  toedev_list ; 
 int /*<<< orphan*/  toedev_lock ; 

__attribute__((used)) static int
toecore_unload(void)
{

	mtx_lock(&toedev_lock);
	if (!TAILQ_EMPTY(&toedev_list)) {
		mtx_unlock(&toedev_lock);
		return (EBUSY);
	}

	EVENTHANDLER_DEREGISTER(tcp_offload_listen_start, listen_start_eh);
	EVENTHANDLER_DEREGISTER(tcp_offload_listen_stop, listen_stop_eh);
	EVENTHANDLER_DEREGISTER(lle_event, lle_event_eh);

	mtx_unlock(&toedev_lock);
	mtx_destroy(&toedev_lock);

	return (0);
}