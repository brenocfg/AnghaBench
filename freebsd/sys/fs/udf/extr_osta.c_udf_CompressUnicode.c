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
typedef  int unicode_t ;
typedef  int byte ;

/* Variables and functions */

int
udf_CompressUnicode(
	int numberOfChars,	/* (Input) number of unicode characters. */
	int compID,		/* (Input) compression ID to be used. */
	unicode_t *unicode,	/* (Input) unicode characters to compress. */
	byte *UDFCompressed)	/* (Output) compressed string, as bytes. */
{
	int byteIndex, unicodeIndex;

	if (compID != 8 && compID != 16) {
		byteIndex = -1; /* Unsupported compression ID ! */
	} else {
		/* Place compression code in first byte. */
		UDFCompressed[0] = compID;

		byteIndex = 1;
		unicodeIndex = 0;
		while (unicodeIndex < numberOfChars) {
			if (compID == 16) {
				/* First, place the high bits of the char
				 * into the byte stream.
				 */
				UDFCompressed[byteIndex++] =
				    (unicode[unicodeIndex] & 0xFF00) >> 8;
			}
			/*Then place the low bits into the stream. */
			UDFCompressed[byteIndex++] =
			    unicode[unicodeIndex] & 0x00FF;
			unicodeIndex++;
		}
	}
	return(byteIndex);
}