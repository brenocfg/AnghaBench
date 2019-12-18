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
 int RBD_SINGLE_MAJOR_PART_SHIFT ; 

__attribute__((used)) static int minor_to_rbd_dev_id(int minor)
{
	return minor >> RBD_SINGLE_MAJOR_PART_SHIFT;
}