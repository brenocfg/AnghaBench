#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
struct TYPE_6__ {TYPE_2__* type; TYPE_1__* dtype; } ;
struct TYPE_5__ {int sect_mult; } ;
struct TYPE_4__ {int sects; } ;

/* Variables and functions */
 unsigned long* ms_putsec (int,unsigned long*,int) ; 
 scalar_t__ raw_buf ; 
 TYPE_3__* unit ; 

__attribute__((used)) static void dos_write(int disk)
{
	int cnt;
	unsigned long raw = (unsigned long) raw_buf;
	unsigned long *ptr=(unsigned long *)raw;

	disk&=3;
/* really gap4 + indexgap , but we write it first and round it up */
	for (cnt=0;cnt<425;cnt++)
		*ptr++=0x92549254;

/* the following is just guessed */
	if (unit[disk].type->sect_mult==2)  /* check for HD-Disks */
		for(cnt=0;cnt<473;cnt++)
			*ptr++=0x92549254;

/* now the index marks...*/
	for (cnt=0;cnt<20;cnt++)
		*ptr++=0x92549254;
	for (cnt=0;cnt<6;cnt++)
		*ptr++=0xaaaaaaaa;
	*ptr++=0x52245224;
	*ptr++=0x52245552;
	for (cnt=0;cnt<20;cnt++)
		*ptr++=0x92549254;

/* sectors */
	for(cnt = 0; cnt < unit[disk].dtype->sects * unit[disk].type->sect_mult; cnt++)
		ptr=ms_putsec(disk,ptr,cnt);

	*(ushort *)ptr = 0xaaa8; /* MFM word before is always 0x9254 */
}