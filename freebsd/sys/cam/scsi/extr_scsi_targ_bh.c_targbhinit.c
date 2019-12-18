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
typedef  scalar_t__ cam_status ;

/* Variables and functions */
 int AC_PATH_DEREGISTERED ; 
 int AC_PATH_REGISTERED ; 
 scalar_t__ CAM_REQ_CMP ; 
 int /*<<< orphan*/  printf (char*,scalar_t__) ; 
 int /*<<< orphan*/  targbhasync ; 
 scalar_t__ xpt_register_async (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
targbhinit(void)
{
	cam_status status;

	/*
	 * Install a global async callback.  This callback will
	 * receive async callbacks like "new path registered".
	 */
	status = xpt_register_async(AC_PATH_REGISTERED | AC_PATH_DEREGISTERED,
				    targbhasync, NULL, NULL);

	if (status != CAM_REQ_CMP) {
		printf("targbh: Failed to attach master async callback "
		       "due to status 0x%x!\n", status);
	}
}