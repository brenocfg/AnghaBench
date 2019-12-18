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

__attribute__((used)) static const char *lwo_lwIDToStr( unsigned int lwID ){
	static char lwIDStr[5];

	if ( !lwID ) {
		return "n/a";
	}

	lwIDStr[ 0 ] = (char)( ( lwID ) >> 24 );
	lwIDStr[ 1 ] = (char)( ( lwID ) >> 16 );
	lwIDStr[ 2 ] = (char)( ( lwID ) >> 8 );
	lwIDStr[ 3 ] = (char)( ( lwID ) );
	lwIDStr[ 4 ] = '\0';

	return lwIDStr;
}