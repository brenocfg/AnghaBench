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
udf_UncompressUnicode(
	int numberOfBytes,	/* (Input) number of bytes read from media. */
	byte *UDFCompressed,	/* (Input) bytes read from media. */
	unicode_t *unicode)	/* (Output) uncompressed unicode characters. */
{
	unsigned int compID;
	int returnValue, unicodeIndex, byteIndex;

	/* Use UDFCompressed to store current byte being read. */
	compID = UDFCompressed[0];

	/* First check for valid compID. */
	if (compID != 8 && compID != 16) {
		returnValue = -1;
	} else {
		unicodeIndex = 0;
		byteIndex = 1;

		/* Loop through all the bytes. */
		while (byteIndex < numberOfBytes) {
			if (compID == 16) {
				/* Move the first byte to the high bits of the
				 * unicode char.
				 */
				unicode[unicodeIndex] =
				    UDFCompressed[byteIndex++] << 8;
			} else {
				unicode[unicodeIndex] = 0;
			}
			if (byteIndex < numberOfBytes) {
				/*Then the next byte to the low bits. */
				unicode[unicodeIndex] |=
				    UDFCompressed[byteIndex++];
			}
			unicodeIndex++;
		}
		returnValue = unicodeIndex;
	}
	return(returnValue);
}