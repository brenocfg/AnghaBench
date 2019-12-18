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
 int ATA_PIO ; 

__attribute__((used)) static int
ata_iobus_sub_setmode(device_t parent, int target, int mode)
{
	/* Only ever PIO mode here... */
	return (ATA_PIO);
}