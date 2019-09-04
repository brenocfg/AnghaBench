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
 scalar_t__ floor (double) ; 

__attribute__((used)) static float range( float v, float lo, float hi, int *i ){
	float v2, r = hi - lo;

	if ( r == 0.0 ) {
		if ( i ) {
			*i = 0;
		}
		return lo;
	}

	v2 = lo + v - r * ( float ) floor( ( double ) v / r );
	if ( i ) {
		*i = -( int )( ( v2 - v ) / r + ( v2 > v ? 0.5 : -0.5 ) );
	}

	return v2;
}