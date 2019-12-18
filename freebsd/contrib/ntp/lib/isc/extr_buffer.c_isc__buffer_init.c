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
 int /*<<< orphan*/  ISC__BUFFER_INIT (int /*<<< orphan*/ *,void const*,unsigned int) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

void
isc__buffer_init(isc_buffer_t *b, const void *base, unsigned int length) {
	/*
	 * Make 'b' refer to the 'length'-byte region starting at 'base'.
	 * XXXDCL see the comment in buffer.h about base being const.
	 */

	REQUIRE(b != NULL);

	ISC__BUFFER_INIT(b, base, length);
}