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
struct cdrom_device_info {int mmc3_profile; } ;

/* Variables and functions */

__attribute__((used)) static int cdrom_is_dvd_rw(struct cdrom_device_info *cdi)
{
	switch (cdi->mmc3_profile) {
	case 0x12:	/* DVD-RAM	*/
	case 0x1A:	/* DVD+RW	*/
	case 0x43:	/* BD-RE	*/
		return 0;
	default:
		return 1;
	}
}