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
 int /*<<< orphan*/  remote_accept_callback ; 
 int /*<<< orphan*/  remote_control_callback ; 
 int /*<<< orphan*/  tube_handle_listen ; 
 int /*<<< orphan*/  tube_handle_write ; 

int 
fptr_whitelist_comm_point_raw(comm_point_callback_type *fptr)
{
	if(fptr == &tube_handle_listen) return 1;
	else if(fptr == &tube_handle_write) return 1;
	else if(fptr == &remote_accept_callback) return 1;
	else if(fptr == &remote_control_callback) return 1;
	return 0;
}