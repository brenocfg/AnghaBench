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
typedef  int /*<<< orphan*/  comm_point_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  auth_xfer_probe_udp_callback ; 
 int /*<<< orphan*/  auth_xfer_transfer_http_callback ; 
 int /*<<< orphan*/  auth_xfer_transfer_tcp_callback ; 
 int /*<<< orphan*/  outnet_tcp_cb ; 
 int /*<<< orphan*/  outnet_udp_cb ; 
 int /*<<< orphan*/  tube_handle_listen ; 
 int /*<<< orphan*/  worker_handle_request ; 

int 
fptr_whitelist_comm_point(comm_point_callback_type *fptr)
{
	if(fptr == &worker_handle_request) return 1;
	else if(fptr == &outnet_udp_cb) return 1;
	else if(fptr == &outnet_tcp_cb) return 1;
	else if(fptr == &tube_handle_listen) return 1;
	else if(fptr == &auth_xfer_probe_udp_callback) return 1;
	else if(fptr == &auth_xfer_transfer_tcp_callback) return 1;
	else if(fptr == &auth_xfer_transfer_http_callback) return 1;
	return 0;
}