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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int fgetc (int /*<<< orphan*/ *) ; 

int fgetLittleLong( FILE *f ){
	byte b1, b2, b3, b4;

	b1 = fgetc( f );
	b2 = fgetc( f );
	b3 = fgetc( f );
	b4 = fgetc( f );

	return b1 + ( b2 << 8 ) + ( b3 << 16 ) + ( b4 << 24 );
}