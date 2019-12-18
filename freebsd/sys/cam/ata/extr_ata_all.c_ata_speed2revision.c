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
typedef  int u_int ;

/* Variables and functions */

int
ata_speed2revision(u_int speed)
{
	switch (speed) {
	case 0:
		return (0);
	case 150000:
		return (1);
	case 300000:
		return (2);
	case 600000:
		return (3);
	default:
		return (-1);
	}
}