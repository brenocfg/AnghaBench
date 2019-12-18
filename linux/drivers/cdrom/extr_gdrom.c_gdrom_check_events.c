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
 unsigned int DISK_EVENT_MEDIA_CHANGE ; 
 int /*<<< orphan*/  GDROM_ERROR_REG ; 
 int __raw_readb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int gdrom_check_events(struct cdrom_device_info *cd_info,
				       unsigned int clearing, int ignore)
{
	/* check the sense key */
	return (__raw_readb(GDROM_ERROR_REG) & 0xF0) == 0x60 ?
		DISK_EVENT_MEDIA_CHANGE : 0;
}