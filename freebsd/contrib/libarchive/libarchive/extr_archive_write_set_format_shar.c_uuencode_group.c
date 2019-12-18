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
 char UUENC (int) ; 

__attribute__((used)) static void
uuencode_group(const char _in[3], char out[4])
{
	const unsigned char *in = (const unsigned char *)_in;
	int t;

	t = (in[0] << 16) | (in[1] << 8) | in[2];
	out[0] = UUENC( 0x3f & (t >> 18) );
	out[1] = UUENC( 0x3f & (t >> 12) );
	out[2] = UUENC( 0x3f & (t >> 6) );
	out[3] = UUENC( 0x3f & t );
}