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

__attribute__((used)) static __inline__ int
nlm_ucore_get_cam_result(unsigned int cam_result)
{
	if (((cam_result >> 15) & 0x1) == 1) /* valid result */
	    return (cam_result & 0x3fff);

	return 0;
}