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
typedef  int vec_accu_t ;
typedef  int* vec3_accu_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (int*) ; 
 scalar_t__ sqrt (int) ; 

vec_accu_t VectorNormalizeAccu( const vec3_accu_t in, vec3_accu_t out ){
	// The sqrt() function takes double as an input and returns double as an
	// output according the the man pages on Debian and on FreeBSD.  Therefore,
	// I don't see a reason why using a double outright (instead of using the
	// vec_accu_t alias for example) could possibly be frowned upon.

	vec_accu_t length;

	length = (vec_accu_t) sqrt( ( in[0] * in[0] ) + ( in[1] * in[1] ) + ( in[2] * in[2] ) );
	if ( length == 0 ) {
		VectorClear( out );
		return 0;
	}

	out[0] = in[0] / length;
	out[1] = in[1] / length;
	out[2] = in[2] / length;

	return length;
}