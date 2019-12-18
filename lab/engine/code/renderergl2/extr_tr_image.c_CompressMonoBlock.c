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
typedef  int byte ;

/* Variables and functions */
 int MAX (int const,int) ; 
 int MIN (int const,int) ; 

__attribute__((used)) static void CompressMonoBlock(byte outdata[8], const byte indata[16])
{
	int hi, lo, diff, bias, outbyte, shift, i;
	byte *p = outdata;

	hi = lo = indata[0];
	for (i = 1; i < 16; i++)
	{
		hi = MAX(indata[i], hi);
		lo = MIN(indata[i], lo);
	}

	*p++ = hi;
	*p++ = lo;

	diff = hi - lo;

	if (diff == 0)
	{
		outbyte = (hi == 255) ? 255 : 0;

		for (i = 0; i < 6; i++)
			*p++ = outbyte;

		return;
	}

	bias = diff / 2 - lo * 7;
	outbyte = shift = 0;
	for (i = 0; i < 16; i++)
	{
		const byte fixIndex[8] = { 1, 7, 6, 5, 4, 3, 2, 0 };
		byte index = fixIndex[(indata[i] * 7 + bias) / diff];

		outbyte |= index << shift;
		shift += 3;
		if (shift >= 8)
		{
			*p++ = outbyte & 0xff;
			shift -= 8;
			outbyte >>= 8;
		}
	}
}