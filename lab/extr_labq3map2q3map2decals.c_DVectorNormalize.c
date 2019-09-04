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
typedef  double dvec_t ;
typedef  double* dvec3_t ;

/* Variables and functions */
 int /*<<< orphan*/  VectorClear (double*) ; 
 scalar_t__ sqrt (double) ; 

dvec_t DVectorNormalize( dvec3_t in, dvec3_t out ){
	dvec_t len, ilen;


	len = (dvec_t) sqrt( in[ 0 ] * in[ 0 ] + in[ 1 ] * in[ 1 ] + in[ 2 ] * in[ 2 ] );
	if ( len == 0.0 ) {
		VectorClear( out );
		return 0.0;
	}

	ilen = 1.0 / len;
	out[ 0 ] = in[ 0 ] * ilen;
	out[ 1 ] = in[ 1 ] * ilen;
	out[ 2 ] = in[ 2 ] * ilen;

	return len;
}