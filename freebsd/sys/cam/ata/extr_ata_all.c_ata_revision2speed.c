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

u_int
ata_revision2speed(int revision)
{
	switch (revision) {
	case 1:
	default:
		return (150000);
	case 2:
		return (300000);
	case 3:
		return (600000);
	}
}