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
struct cdrom_device_info {int dummy; } ;

/* Variables and functions */
 int cdrom_media_erasable (struct cdrom_device_info*) ; 

__attribute__((used)) static int cdrom_dvdram_open_write(struct cdrom_device_info *cdi)
{
	int ret = cdrom_media_erasable(cdi);

	/*
	 * allow writable open if media info read worked and media is
	 * erasable, _or_ if it fails since not all drives support it
	 */
	if (!ret)
		return 1;

	return 0;
}