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

unsigned char sgetU1( unsigned char **bp ){
	unsigned char c;

	if ( flen == FLEN_ERROR ) {
		return 0;
	}
	c = **bp;
	flen += 1;
	( *bp )++;
	return c;
}