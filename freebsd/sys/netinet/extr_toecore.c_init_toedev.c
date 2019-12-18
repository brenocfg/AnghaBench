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
struct toedev {int /*<<< orphan*/  tod_alloc_tls_session; int /*<<< orphan*/  tod_tcp_info; int /*<<< orphan*/  tod_ctloutput; int /*<<< orphan*/  tod_offload_socket; int /*<<< orphan*/  tod_syncache_respond; int /*<<< orphan*/  tod_syncache_removed; int /*<<< orphan*/  tod_syncache_added; int /*<<< orphan*/  tod_route_redirect; int /*<<< orphan*/  tod_l2_update; int /*<<< orphan*/  tod_pcb_detach; void* tod_send_fin; void* tod_send_rst; void* tod_output; int /*<<< orphan*/  tod_rcvd; int /*<<< orphan*/  tod_input; int /*<<< orphan*/  tod_listen_stop; int /*<<< orphan*/  tod_listen_start; int /*<<< orphan*/  tod_connect; int /*<<< orphan*/ * tod_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  toedev_alloc_tls_session ; 
 int /*<<< orphan*/  toedev_connect ; 
 int /*<<< orphan*/  toedev_ctloutput ; 
 int /*<<< orphan*/  toedev_input ; 
 int /*<<< orphan*/  toedev_l2_update ; 
 int /*<<< orphan*/  toedev_listen_start ; 
 int /*<<< orphan*/  toedev_listen_stop ; 
 int /*<<< orphan*/  toedev_offload_socket ; 
 void* toedev_output ; 
 int /*<<< orphan*/  toedev_pcb_detach ; 
 int /*<<< orphan*/  toedev_rcvd ; 
 int /*<<< orphan*/  toedev_route_redirect ; 
 int /*<<< orphan*/  toedev_syncache_added ; 
 int /*<<< orphan*/  toedev_syncache_removed ; 
 int /*<<< orphan*/  toedev_syncache_respond ; 
 int /*<<< orphan*/  toedev_tcp_info ; 

void
init_toedev(struct toedev *tod)
{

	tod->tod_softc = NULL;

	/*
	 * Provide no-op defaults so that the kernel can call any toedev
	 * function without having to check whether the TOE driver supplied one
	 * or not.
	 */
	tod->tod_connect = toedev_connect;
	tod->tod_listen_start = toedev_listen_start;
	tod->tod_listen_stop = toedev_listen_stop;
	tod->tod_input = toedev_input;
	tod->tod_rcvd = toedev_rcvd;
	tod->tod_output = toedev_output;
	tod->tod_send_rst = toedev_output;
	tod->tod_send_fin = toedev_output;
	tod->tod_pcb_detach = toedev_pcb_detach;
	tod->tod_l2_update = toedev_l2_update;
	tod->tod_route_redirect = toedev_route_redirect;
	tod->tod_syncache_added = toedev_syncache_added;
	tod->tod_syncache_removed = toedev_syncache_removed;
	tod->tod_syncache_respond = toedev_syncache_respond;
	tod->tod_offload_socket = toedev_offload_socket;
	tod->tod_ctloutput = toedev_ctloutput;
	tod->tod_tcp_info = toedev_tcp_info;
	tod->tod_alloc_tls_session = toedev_alloc_tls_session;
}