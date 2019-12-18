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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGP_ACQUIRE_KERNEL ; 
 int agp_acquire_helper (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
agp_acquire(device_t dev)
{
	return agp_acquire_helper(dev, AGP_ACQUIRE_KERNEL);
}