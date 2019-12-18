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
typedef  int /*<<< orphan*/  picoVertexCombinationHash_t ;

/* Variables and functions */
 int HASHTABLE_SIZE ; 
 int /*<<< orphan*/ ** _pico_alloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 

picoVertexCombinationHash_t **PicoNewVertexCombinationHashTable( void ){
	picoVertexCombinationHash_t **hashTable = _pico_alloc( HASHTABLE_SIZE * sizeof( picoVertexCombinationHash_t* ) );

	memset( hashTable, 0, HASHTABLE_SIZE * sizeof( picoVertexCombinationHash_t* ) );

	return hashTable;
}