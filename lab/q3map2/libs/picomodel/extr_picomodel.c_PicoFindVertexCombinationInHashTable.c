#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* xyz; scalar_t__* normal; scalar_t__* st; scalar_t__ color; } ;
struct TYPE_6__ {TYPE_1__ vcd; struct TYPE_6__* next; } ;
typedef  TYPE_2__ picoVertexCombinationHash_t ;
typedef  scalar_t__* picoVec3_t ;
typedef  int /*<<< orphan*/ * picoColor_t ;

/* Variables and functions */
 scalar_t__ HASH_NORMAL_EPSILON ; 
 scalar_t__ HASH_ST_EPSILON ; 
 scalar_t__ HASH_XYZ_EPSILON ; 
 unsigned int PicoVertexCoordGenerateHash (scalar_t__*) ; 
 scalar_t__ fabs (scalar_t__) ; 

picoVertexCombinationHash_t *PicoFindVertexCombinationInHashTable( picoVertexCombinationHash_t **hashTable, picoVec3_t xyz, picoVec3_t normal, picoVec3_t st, picoColor_t color ){
	unsigned int hash;
	picoVertexCombinationHash_t *vertexCombinationHash;

	/* dumy check */
	if ( hashTable == NULL || xyz == NULL || normal == NULL || st == NULL || color == NULL ) {
		return NULL;
	}

	hash = PicoVertexCoordGenerateHash( xyz );

	for ( vertexCombinationHash = hashTable[ hash ]; vertexCombinationHash; vertexCombinationHash = vertexCombinationHash->next )
	{
#ifndef HASH_USE_EPSILON
		/* check xyz */
		if ( ( vertexCombinationHash->vcd.xyz[ 0 ] != xyz[ 0 ] || vertexCombinationHash->vcd.xyz[ 1 ] != xyz[ 1 ] || vertexCombinationHash->vcd.xyz[ 2 ] != xyz[ 2 ] ) ) {
			continue;
		}

		/* check normal */
		if ( ( vertexCombinationHash->vcd.normal[ 0 ] != normal[ 0 ] || vertexCombinationHash->vcd.normal[ 1 ] != normal[ 1 ] || vertexCombinationHash->vcd.normal[ 2 ] != normal[ 2 ] ) ) {
			continue;
		}

		/* check st */
		if ( vertexCombinationHash->vcd.st[ 0 ] != st[ 0 ] || vertexCombinationHash->vcd.st[ 1 ] != st[ 1 ] ) {
			continue;
		}
#else
		/* check xyz */
		if ( ( fabs( xyz[ 0 ] - vertexCombinationHash->vcd.xyz[ 0 ] ) ) > HASH_XYZ_EPSILON ||
			 ( fabs( xyz[ 1 ] - vertexCombinationHash->vcd.xyz[ 1 ] ) ) > HASH_XYZ_EPSILON ||
			 ( fabs( xyz[ 2 ] - vertexCombinationHash->vcd.xyz[ 2 ] ) ) > HASH_XYZ_EPSILON ) {
			continue;
		}

		/* check normal */
		if ( ( fabs( normal[ 0 ] - vertexCombinationHash->vcd.normal[ 0 ] ) ) > HASH_NORMAL_EPSILON ||
			 ( fabs( normal[ 1 ] - vertexCombinationHash->vcd.normal[ 1 ] ) ) > HASH_NORMAL_EPSILON ||
			 ( fabs( normal[ 2 ] - vertexCombinationHash->vcd.normal[ 2 ] ) ) > HASH_NORMAL_EPSILON ) {
			continue;
		}

		/* check st */
		if ( ( fabs( st[ 0 ] - vertexCombinationHash->vcd.st[ 0 ] ) ) > HASH_ST_EPSILON ||
			 ( fabs( st[ 1 ] - vertexCombinationHash->vcd.st[ 1 ] ) ) > HASH_ST_EPSILON ) {
			continue;
		}
#endif

		/* check color */
		if ( *( (int*) vertexCombinationHash->vcd.color ) != *( (int*) color ) ) {
			continue;
		}

		/* gotcha */
		return vertexCombinationHash;
	}

	return NULL;
}