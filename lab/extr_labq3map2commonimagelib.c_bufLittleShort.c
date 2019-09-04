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
 int /*<<< orphan*/  Error (char*) ; 

int bufLittleShort( byte *buf, int len, int *pos ){
	byte b1, b2;

	if ( ( len - *pos ) < 2 ) {
		Error( "Unexpected buffer end" );
	}

	b1 = buf[*pos]; *pos += 1;
	b2 = buf[*pos]; *pos += 1;

	return (short)( b1 + b2 * 256 );
}