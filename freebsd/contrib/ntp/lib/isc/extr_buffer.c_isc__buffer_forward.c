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
struct TYPE_5__ {scalar_t__ current; scalar_t__ used; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  ISC__BUFFER_FORWARD (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc__buffer_forward(isc_buffer_t *b, unsigned int n) {
	/*
	 * Increase the 'consumed' region of 'b' by 'n' bytes.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(b->current + n <= b->used);

	ISC__BUFFER_FORWARD(b, n);
}