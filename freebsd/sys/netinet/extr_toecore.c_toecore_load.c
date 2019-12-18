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
 int /*<<< orphan*/  EVENTHANDLER_PRI_ANY ; 
 void* EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 void* listen_start_eh ; 
 void* listen_stop_eh ; 
 int /*<<< orphan*/  lle_event ; 
 void* lle_event_eh ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_offload_listen_start ; 
 int /*<<< orphan*/  tcp_offload_listen_stop ; 
 int /*<<< orphan*/  toe_listen_start_event ; 
 int /*<<< orphan*/  toe_listen_stop_event ; 
 int /*<<< orphan*/  toe_lle_event ; 
 int /*<<< orphan*/  toedev_list ; 
 int /*<<< orphan*/  toedev_lock ; 

__attribute__((used)) static int
toecore_load(void)
{

	mtx_init(&toedev_lock, "toedev lock", NULL, MTX_DEF);
	TAILQ_INIT(&toedev_list);

	listen_start_eh = EVENTHANDLER_REGISTER(tcp_offload_listen_start,
	    toe_listen_start_event, NULL, EVENTHANDLER_PRI_ANY);
	listen_stop_eh = EVENTHANDLER_REGISTER(tcp_offload_listen_stop,
	    toe_listen_stop_event, NULL, EVENTHANDLER_PRI_ANY);
	lle_event_eh = EVENTHANDLER_REGISTER(lle_event, toe_lle_event, NULL,
	    EVENTHANDLER_PRI_ANY);

	return (0);
}