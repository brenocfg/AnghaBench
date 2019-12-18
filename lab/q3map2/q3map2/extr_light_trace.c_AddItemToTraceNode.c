#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int numItems; int maxItems; int* items; } ;
typedef  TYPE_1__ traceNode_t ;

/* Variables and functions */
 int GROW_NODE_ITEMS ; 
 int /*<<< orphan*/  free (int*) ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 void* safe_malloc (int) ; 
 TYPE_1__* traceNodes ; 

__attribute__((used)) static int AddItemToTraceNode( traceNode_t *node, int num ){
	void            *temp;


	/* dummy check */
	if ( num < 0 ) {
		return -1;
	}

	/* enough space? */
	if ( node->numItems >= node->maxItems ) {
		/* allocate more room */
		if ( node == traceNodes ) {
			node->maxItems *= 2;
		}
		else{
			node->maxItems += GROW_NODE_ITEMS;
		}
		if ( node->maxItems <= 0 ) {
			node->maxItems = GROW_NODE_ITEMS;
		}
		temp = safe_malloc( node->maxItems * sizeof( *node->items ) );
		if ( node->items != NULL ) {
			memcpy( temp, node->items, node->numItems * sizeof( *node->items ) );
			free( node->items );
		}
		node->items = (int*) temp;
	}

	/* add the poly */
	node->items[ node->numItems ] = num;
	node->numItems++;

	/* return the count */
	return ( node->numItems - 1 );
}