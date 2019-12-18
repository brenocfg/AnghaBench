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

__attribute__((used)) static void j_putRGBScanline( unsigned char* jpegline, int widthPix, unsigned char* outBuf, int row ){
	int offset = row * widthPix * 4;
	int count;

	for ( count = 0; count < widthPix; count++ )
	{
		unsigned char iRed, iBlu, iGrn;
		unsigned char *oRed, *oBlu, *oGrn, *oAlp;

		iRed = *( jpegline + count * 3 + 0 );
		iGrn = *( jpegline + count * 3 + 1 );
		iBlu = *( jpegline + count * 3 + 2 );

		oRed = outBuf + offset + count * 4 + 0;
		oGrn = outBuf + offset + count * 4 + 1;
		oBlu = outBuf + offset + count * 4 + 2;
		oAlp = outBuf + offset + count * 4 + 3;

		*oRed = iRed;
		*oGrn = iGrn;
		*oBlu = iBlu;
		*oAlp = 255;
	}
}