#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  byte ;
struct TYPE_4__ {int /*<<< orphan*/ * mcomp; } ;
struct TYPE_3__ {int samplesPerLine; } ;

/* Variables and functions */
 int /*<<< orphan*/  blit2_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blit4_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  blit8_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ cin ; 
 TYPE_1__* cinTable ; 
 size_t currentHandle ; 
 int /*<<< orphan*/  move4_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  move8_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vq2 ; 
 int /*<<< orphan*/ * vq4 ; 
 int /*<<< orphan*/ * vq8 ; 

__attribute__((used)) static void blitVQQuad32fs( byte **status, unsigned char *data )
{
unsigned short	newd, celdata, code;
unsigned int	index, i;
int		spl;

	newd	= 0;
	celdata = 0;
	index	= 0;
	
        spl = cinTable[currentHandle].samplesPerLine;
        
	do {
		if (!newd) { 
			newd = 7;
			celdata = data[0] + data[1]*256;
			data += 2;
		} else {
			newd--;
		}

		code = (unsigned short)(celdata&0xc000); 
		celdata <<= 2;
		
		switch (code) {
			case	0x8000:													// vq code
				blit8_32( (byte *)&vq8[(*data)*128], status[index], spl );
				data++;
				index += 5;
				break;
			case	0xc000:													// drop
				index++;													// skip 8x8
				for(i=0;i<4;i++) {
					if (!newd) { 
						newd = 7;
						celdata = data[0] + data[1]*256;
						data += 2;
					} else {
						newd--;
					}
						
					code = (unsigned short)(celdata&0xc000); celdata <<= 2; 

					switch (code) {											// code in top two bits of code
						case	0x8000:										// 4x4 vq code
							blit4_32( (byte *)&vq4[(*data)*32], status[index], spl );
							data++;
							break;
						case	0xc000:										// 2x2 vq code
							blit2_32( (byte *)&vq2[(*data)*8], status[index], spl );
							data++;
							blit2_32( (byte *)&vq2[(*data)*8], status[index]+8, spl );
							data++;
							blit2_32( (byte *)&vq2[(*data)*8], status[index]+spl*2, spl );
							data++;
							blit2_32( (byte *)&vq2[(*data)*8], status[index]+spl*2+8, spl );
							data++;
							break;
						case	0x4000:										// motion compensation
							move4_32( status[index] + cin.mcomp[(*data)], status[index], spl );
							data++;
							break;
					}
					index++;
				}
				break;
			case	0x4000:													// motion compensation
				move8_32( status[index] + cin.mcomp[(*data)], status[index], spl );
				data++;
				index += 5;
				break;
			case	0x0000:
				index += 5;
				break;
		}
	} while ( status[index] != NULL );
}