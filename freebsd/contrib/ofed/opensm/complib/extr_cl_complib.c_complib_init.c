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
typedef  scalar_t__ cl_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  CL_STATUS_MSG (scalar_t__) ; 
 scalar_t__ CL_SUCCESS ; 
 scalar_t__ __cl_timer_prov_create () ; 
 int /*<<< orphan*/  cl_atomic_spinlock ; 
 int /*<<< orphan*/  cl_msg_out (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cl_spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exit (int) ; 

void complib_init(void)
{
	cl_status_t status = CL_SUCCESS;

	status = cl_spinlock_init(&cl_atomic_spinlock);
	if (status != CL_SUCCESS)
		goto _error;

	status = __cl_timer_prov_create();
	if (status != CL_SUCCESS)
		goto _error;
	return;

_error:
	cl_msg_out("__init: failed to create complib (%s)\n",
		   CL_STATUS_MSG(status));
	exit(1);
}