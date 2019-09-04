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
typedef  int byte ;
struct TYPE_2__ {int* buf; int CIN_WIDTH; int CIN_HEIGHT; } ;

/* Variables and functions */
 TYPE_1__* cinTable ; 

void CIN_ResampleCinematic(int handle, int *buf2) {
	int ix, iy, *buf3, xm, ym, ll;
	byte	*buf;

	buf = cinTable[handle].buf;

	xm = cinTable[handle].CIN_WIDTH/256;
	ym = cinTable[handle].CIN_HEIGHT/256;
	ll = 8;
	if (cinTable[handle].CIN_WIDTH==512) {
		ll = 9;
	}

	buf3 = (int*)buf;
	if (xm==2 && ym==2) {
		byte *bc2, *bc3;
		int	ic, iiy;

		bc2 = (byte *)buf2;
		bc3 = (byte *)buf3;
		for (iy = 0; iy<256; iy++) {
			iiy = iy<<12;
			for (ix = 0; ix<2048; ix+=8) {
				for(ic = ix;ic<(ix+4);ic++) {
					*bc2=(bc3[iiy+ic]+bc3[iiy+4+ic]+bc3[iiy+2048+ic]+bc3[iiy+2048+4+ic])>>2;
					bc2++;
				}
			}
		}
	} else if (xm==2 && ym==1) {
		byte *bc2, *bc3;
		int	ic, iiy;

		bc2 = (byte *)buf2;
		bc3 = (byte *)buf3;
		for (iy = 0; iy<256; iy++) {
			iiy = iy<<11;
			for (ix = 0; ix<2048; ix+=8) {
				for(ic = ix;ic<(ix+4);ic++) {
					*bc2=(bc3[iiy+ic]+bc3[iiy+4+ic])>>1;
					bc2++;
				}
			}
		}
	} else {
		for (iy = 0; iy<256; iy++) {
			for (ix = 0; ix<256; ix++) {
					buf2[(iy<<8)+ix] = buf3[((iy*ym)<<ll) + (ix*xm)];
			}
		}
	}
}