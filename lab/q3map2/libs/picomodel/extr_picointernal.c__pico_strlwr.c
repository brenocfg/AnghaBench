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

char *_pico_strlwr( char *str ){
	char *cp;
	for ( cp = str; *cp; ++cp )
	{
		if ( 'A' <= *cp && *cp <= 'Z' ) {
			*cp += ( 'a' - 'A' );
		}
	}
	return str;
}