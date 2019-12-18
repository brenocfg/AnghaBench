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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  iic_dp_aux_reset_bus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iic_dp_aux_reset(device_t idev, u_char speed, u_char addr, u_char *oldaddr)
{

	iic_dp_aux_reset_bus(idev);
	return (0);
}