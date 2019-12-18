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
struct a10codec_chinfo {int speed; } ;

/* Variables and functions */
 int DAC_FS_12KHZ ; 
 int DAC_FS_16KHZ ; 
 int DAC_FS_192KHZ ; 
 int DAC_FS_24KHZ ; 
 int DAC_FS_32KHZ ; 
 int DAC_FS_48KHZ ; 
 int DAC_FS_8KHZ ; 
 int DAC_FS_96KHZ ; 

__attribute__((used)) static unsigned
a10codec_fs(struct a10codec_chinfo *ch)
{
	switch (ch->speed) {
	case 48000:
		return (DAC_FS_48KHZ);
	case 24000:
		return (DAC_FS_24KHZ);
	case 12000:
		return (DAC_FS_12KHZ);
	case 192000:
		return (DAC_FS_192KHZ);
	case 32000:
		return (DAC_FS_32KHZ);
	case 16000:
		return (DAC_FS_16KHZ);
	case 8000:
		return (DAC_FS_8KHZ);
	case 96000:
		return (DAC_FS_96KHZ);
	default:
		return (DAC_FS_48KHZ);
	}
}