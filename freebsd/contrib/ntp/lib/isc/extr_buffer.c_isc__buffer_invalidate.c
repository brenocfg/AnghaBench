#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * mctx; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  ISC_LINK_LINKED (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISC__BUFFER_INVALIDATE (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  link ; 

void
isc__buffer_invalidate(isc_buffer_t *b) {
	/*
	 * Make 'b' an invalid buffer.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(!ISC_LINK_LINKED(b, link));
	REQUIRE(b->mctx == NULL);

	ISC__BUFFER_INVALIDATE(b);
}