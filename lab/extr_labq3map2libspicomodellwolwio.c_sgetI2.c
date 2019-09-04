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
 int /*<<< orphan*/  memcpy (short*,unsigned char*,int) ; 
 int /*<<< orphan*/  revbytes (short*,int,int) ; 

short sgetI2( unsigned char **bp ){
	short i;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}
	memcpy( &i, *bp, 2 );
	revbytes( &i, 2, 1 );
	flen += 2;
	*bp += 2;
	return i;
}