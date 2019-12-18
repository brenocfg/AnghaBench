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
typedef  int* in2 ;
typedef  int* in ;
typedef  size_t byte ;

/* Variables and functions */
 float powf (float,float) ; 

__attribute__((used)) static void R_MipMapsRGB( byte *in, int inWidth, int inHeight)
{
	int x, y, c, stride;
	const byte *in2;
	float total;
	static float downmipSrgbLookup[256];
	static int downmipSrgbLookupSet = 0;
	byte *out = in;

	if (!downmipSrgbLookupSet) {
		for (x = 0; x < 256; x++)
			downmipSrgbLookup[x] = powf(x / 255.0f, 2.2f) * 0.25f;
		downmipSrgbLookupSet = 1;
	}

	if (inWidth == 1 && inHeight == 1)
		return;

	if (inWidth == 1 || inHeight == 1) {
		for (x = (inWidth * inHeight) >> 1; x; x--) {
			for (c = 3; c; c--, in++) {
				total  = (downmipSrgbLookup[*(in)] + downmipSrgbLookup[*(in + 4)]) * 2.0f;

				*out++ = (byte)(powf(total, 1.0f / 2.2f) * 255.0f);
			}
			*out++ = (*(in) + *(in + 4)) >> 1; in += 5;
		}
		
		return;
	}

	stride = inWidth * 4;
	inWidth >>= 1; inHeight >>= 1;

	in2 = in + stride;
	for (y = inHeight; y; y--, in += stride, in2 += stride) {
		for (x = inWidth; x; x--) {
			for (c = 3; c; c--, in++, in2++) {
				total = downmipSrgbLookup[*(in)]  + downmipSrgbLookup[*(in + 4)]
				      + downmipSrgbLookup[*(in2)] + downmipSrgbLookup[*(in2 + 4)];

				*out++ = (byte)(powf(total, 1.0f / 2.2f) * 255.0f);
			}

			*out++ = (*(in) + *(in + 4) + *(in2) + *(in2 + 4)) >> 2; in += 5, in2 += 5;
		}
	}
}