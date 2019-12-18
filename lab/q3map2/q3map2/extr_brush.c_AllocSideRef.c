#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  side_t ;
struct TYPE_5__ {struct TYPE_5__* next; int /*<<< orphan*/ * side; } ;
typedef  TYPE_1__ sideRef_t ;

/* Variables and functions */
 TYPE_1__* safe_malloc (int) ; 

sideRef_t *AllocSideRef( side_t *side, sideRef_t *next ){
	sideRef_t *sideRef;


	/* dummy check */
	if ( side == NULL ) {
		return next;
	}

	/* allocate and return */
	sideRef = safe_malloc( sizeof( *sideRef ) );
	sideRef->side = side;
	sideRef->next = next;
	return sideRef;
}