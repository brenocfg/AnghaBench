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

int CountBits( byte *bits, int numbits ){
	int i;
	int c;

	c = 0;
	for ( i = 0 ; i < numbits ; i++ )
		if ( bits[i >> 3] & ( 1 << ( i & 7 ) ) ) {
			c++;
		}

	return c;
}