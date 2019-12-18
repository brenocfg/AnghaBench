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
typedef  int /*<<< orphan*/  tube_callback_type ;

/* Variables and functions */
 int /*<<< orphan*/  libworker_handle_control_cmd ; 
 int /*<<< orphan*/  worker_handle_control_cmd ; 

int fptr_whitelist_tube_listen(tube_callback_type* fptr)
{
	if(fptr == &worker_handle_control_cmd) return 1;
	else if(fptr == &libworker_handle_control_cmd) return 1;
	return 0;
}