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
 int MLX5_BF_REGS_PER_PAGE ; 
 int NUM_DRIVER_UARS ; 
 int NUM_LOW_LAT_UUARS ; 

__attribute__((used)) static int need_uuar_lock(int uuarn)
{
	int tot_uuars = NUM_DRIVER_UARS * MLX5_BF_REGS_PER_PAGE;

	if (uuarn == 0 || tot_uuars - NUM_LOW_LAT_UUARS)
		return 0;

	return 1;
}