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
typedef  int /*<<< orphan*/ * picoVec3_t ;

/* Variables and functions */
 unsigned int HASHTABLE_SIZE ; 

unsigned int PicoVertexCoordGenerateHash( picoVec3_t xyz ){
	unsigned int hash = 0;

#ifndef HASH_USE_EPSILON
	hash += ~( *( (unsigned int*) &xyz[ 0 ] ) << 15 );
	hash ^= ( *( (unsigned int*) &xyz[ 0 ] ) >> 10 );
	hash += ( *( (unsigned int*) &xyz[ 1 ] ) << 3 );
	hash ^= ( *( (unsigned int*) &xyz[ 1 ] ) >> 6 );
	hash += ~( *( (unsigned int*) &xyz[ 2 ] ) << 11 );
	hash ^= ( *( (unsigned int*) &xyz[ 2 ] ) >> 16 );
#else
	picoVec3_t xyz_epsilonspace;

	_pico_scale_vec( xyz, HASH_XYZ_EPSILONSPACE_MULTIPLIER, xyz_epsilonspace );
	xyz_epsilonspace[ 0 ] = (float)floor( xyz_epsilonspace[ 0 ] );
	xyz_epsilonspace[ 1 ] = (float)floor( xyz_epsilonspace[ 1 ] );
	xyz_epsilonspace[ 2 ] = (float)floor( xyz_epsilonspace[ 2 ] );

	hash += ~( *( (unsigned int*) &xyz_epsilonspace[ 0 ] ) << 15 );
	hash ^= ( *( (unsigned int*) &xyz_epsilonspace[ 0 ] ) >> 10 );
	hash += ( *( (unsigned int*) &xyz_epsilonspace[ 1 ] ) << 3 );
	hash ^= ( *( (unsigned int*) &xyz_epsilonspace[ 1 ] ) >> 6 );
	hash += ~( *( (unsigned int*) &xyz_epsilonspace[ 2 ] ) << 11 );
	hash ^= ( *( (unsigned int*) &xyz_epsilonspace[ 2 ] ) >> 16 );
#endif

	//hash = hash & (HASHTABLE_SIZE-1);
	hash = hash % ( HASHTABLE_SIZE );
	return hash;
}