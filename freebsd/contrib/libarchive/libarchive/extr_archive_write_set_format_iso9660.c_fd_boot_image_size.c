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
#define  BOOT_MEDIA_1_2M_DISKETTE 130 
#define  BOOT_MEDIA_1_44M_DISKETTE 129 
#define  BOOT_MEDIA_2_88M_DISKETTE 128 
 size_t FD_1_2M_SIZE ; 
 size_t FD_1_44M_SIZE ; 
 size_t FD_2_88M_SIZE ; 

__attribute__((used)) static size_t
fd_boot_image_size(int media_type)
{
	switch (media_type) {
	case BOOT_MEDIA_1_2M_DISKETTE:
		return (FD_1_2M_SIZE);
	case BOOT_MEDIA_1_44M_DISKETTE:
		return (FD_1_44M_SIZE);
	case BOOT_MEDIA_2_88M_DISKETTE:
		return (FD_2_88M_SIZE);
	default:
		return (0);
	}
}