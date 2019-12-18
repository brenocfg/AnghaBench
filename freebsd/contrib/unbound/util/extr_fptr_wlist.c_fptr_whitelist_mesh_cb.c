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
typedef  int /*<<< orphan*/ * mesh_cb_func_type ;

/* Variables and functions */
 int /*<<< orphan*/  auth_xfer_probe_lookup_callback ; 
 int /*<<< orphan*/  auth_xfer_transfer_lookup_callback ; 
 int /*<<< orphan*/  libworker_bg_done_cb ; 
 int /*<<< orphan*/  libworker_event_done_cb ; 
 int /*<<< orphan*/  libworker_fg_done_cb ; 
 int /*<<< orphan*/  probe_answer_cb ; 

int fptr_whitelist_mesh_cb(mesh_cb_func_type fptr)
{
	if(fptr == &libworker_fg_done_cb) return 1;
	else if(fptr == &libworker_bg_done_cb) return 1;
	else if(fptr == &libworker_event_done_cb) return 1;
	else if(fptr == &probe_answer_cb) return 1;
	else if(fptr == &auth_xfer_probe_lookup_callback) return 1;
	else if(fptr == &auth_xfer_transfer_lookup_callback) return 1;
	return 0;
}