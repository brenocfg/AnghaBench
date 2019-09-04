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
struct TYPE_2__ {scalar_t__* sqrTable; } ;

/* Variables and functions */
 TYPE_1__ cin ; 

long RllDecodeStereoToStereo(unsigned char *from,short *to,unsigned int size,char signedOutput, unsigned short flag)
{
	unsigned int z;
	unsigned char *zz = from;
	int	prevL, prevR;

	if (signedOutput) {
		prevL = (flag & 0xff00) - 0x8000;
		prevR = ((flag & 0x00ff) << 8) - 0x8000;
	} else {
		prevL = flag & 0xff00;
		prevR = (flag & 0x00ff) << 8;
	}

	for (z=0;z<size;z+=2) {
                prevL = (short)(prevL + cin.sqrTable[*zz++]); 
                prevR = (short)(prevR + cin.sqrTable[*zz++]);
                to[z+0] = (short)(prevL);
                to[z+1] = (short)(prevR);
	}
	
	return (size>>1);	//*sizeof(short));
}