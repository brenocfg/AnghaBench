#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; } ;

/* Variables and functions */
#define  BOOTINFO_DEV_TYPE_CFI 129 
#define  BOOTINFO_DEV_TYPE_SDCARD 128 
 int altera_sdcard_read (void*,unsigned int,unsigned int) ; 
 int cfi_read (void*,unsigned int,unsigned int) ; 
 TYPE_1__ dsk ; 

__attribute__((used)) static int
drvread(void *buf, unsigned lba, unsigned nblk)
{

	/* XXXRW: eventually, we may want to pass 'drive' and 'unit' here. */
	switch (dsk.type) {
	case BOOTINFO_DEV_TYPE_CFI:
		return (cfi_read(buf, lba, nblk));

	case BOOTINFO_DEV_TYPE_SDCARD:
		return (altera_sdcard_read(buf, lba, nblk));

	default:
		return (-1);
	}
}