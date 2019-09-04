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
 scalar_t__ FLEN_ERROR ; 
 scalar_t__ flen ; 

unsigned short sgetU2( unsigned char **bp ){
	unsigned char *buf = *bp;
	unsigned short i;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}
	i = ( buf[ 0 ] << 8 ) | buf[ 1 ];
	flen += 2;
	*bp += 2;
	return i;
}