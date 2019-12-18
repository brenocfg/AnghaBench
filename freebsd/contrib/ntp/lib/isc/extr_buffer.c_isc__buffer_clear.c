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
typedef  int /*<<< orphan*/  isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_BUFFER_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISC__BUFFER_CLEAR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

void
isc__buffer_clear(isc_buffer_t *b) {
	/*
	 * Make the used region empty.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));

	ISC__BUFFER_CLEAR(b);
}