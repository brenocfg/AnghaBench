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

__attribute__((used)) static size_t
utf8(unsigned int cp, char out[7])
{
	size_t		 rc;

	rc = 0;
	if (cp <= 0x0000007F) {
		rc = 1;
		out[0] = (char)cp;
	} else if (cp <= 0x000007FF) {
		rc = 2;
		out[0] = (cp >> 6  & 31) | 192;
		out[1] = (cp       & 63) | 128;
	} else if (cp <= 0x0000FFFF) {
		rc = 3;
		out[0] = (cp >> 12 & 15) | 224;
		out[1] = (cp >> 6  & 63) | 128;
		out[2] = (cp       & 63) | 128;
	} else if (cp <= 0x001FFFFF) {
		rc = 4;
		out[0] = (cp >> 18 &  7) | 240;
		out[1] = (cp >> 12 & 63) | 128;
		out[2] = (cp >> 6  & 63) | 128;
		out[3] = (cp       & 63) | 128;
	} else if (cp <= 0x03FFFFFF) {
		rc = 5;
		out[0] = (cp >> 24 &  3) | 248;
		out[1] = (cp >> 18 & 63) | 128;
		out[2] = (cp >> 12 & 63) | 128;
		out[3] = (cp >> 6  & 63) | 128;
		out[4] = (cp       & 63) | 128;
	} else if (cp <= 0x7FFFFFFF) {
		rc = 6;
		out[0] = (cp >> 30 &  1) | 252;
		out[1] = (cp >> 24 & 63) | 128;
		out[2] = (cp >> 18 & 63) | 128;
		out[3] = (cp >> 12 & 63) | 128;
		out[4] = (cp >> 6  & 63) | 128;
		out[5] = (cp       & 63) | 128;
	} else
		return 0;

	out[rc] = '\0';
	return rc;
}