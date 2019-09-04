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
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 

int _pico_getline( char *buf, int bufsize, char *dest, int destsize ){
	int pos;

	/* check output */
	if ( dest == NULL || destsize < 1 ) {
		return -1;
	}
	memset( dest,0,destsize );

	/* check input */
	if ( buf == NULL || bufsize < 1 ) {
		return -1;
	}

	/* get next line */
	for ( pos = 0; pos < bufsize && pos < destsize; pos++ )
	{
		if ( buf[pos] == '\n' ) {
			pos++; break;
		}
		dest[pos] = buf[pos];
	}
	/* terminate dest and return */
	dest[pos] = '\0';
	return pos;
}