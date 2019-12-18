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
typedef  float vec_t ;
typedef  float* vec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (float*) ; 
 double sqrt (float) ; 

vec_t VectorNormalize( const vec3_t in, vec3_t out ) {

#if MATHLIB_VECTOR_NORMALIZE_PRECISION_FIX

	// The sqrt() function takes double as an input and returns double as an
	// output according the the man pages on Debian and on FreeBSD.  Therefore,
	// I don't see a reason why using a double outright (instead of using the
	// vec_accu_t alias for example) could possibly be frowned upon.

	double x, y, z, length;

	x = (double) in[0];
	y = (double) in[1];
	z = (double) in[2];

	length = sqrt( ( x * x ) + ( y * y ) + ( z * z ) );
	if ( length == 0 ) {
		VectorClear( out );
		return 0;
	}

	out[0] = (vec_t) ( x / length );
	out[1] = (vec_t) ( y / length );
	out[2] = (vec_t) ( z / length );

	return (vec_t) length;

#else

	vec_t length, ilength;

	length = (vec_t)sqrt( in[0] * in[0] + in[1] * in[1] + in[2] * in[2] );
	if ( length == 0 ) {
		VectorClear( out );
		return 0;
	}

	ilength = 1.0f / length;
	out[0] = in[0] * ilength;
	out[1] = in[1] * ilength;
	out[2] = in[2] * ilength;

	return length;

#endif

}