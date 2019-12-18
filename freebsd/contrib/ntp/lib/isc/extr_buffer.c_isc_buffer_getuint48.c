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
typedef  int isc_uint64_t ;
typedef  int isc_int64_t ;
struct TYPE_5__ {int used; int current; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 unsigned char* isc_buffer_current (TYPE_1__*) ; 

isc_uint64_t
isc_buffer_getuint48(isc_buffer_t *b) {
	unsigned char *cp;
	isc_uint64_t result;

	/*
	 * Read an unsigned 48-bit integer in network byte order from 'b',
	 * convert it to host byte order, and return it.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(b->used - b->current >= 6);

	cp = isc_buffer_current(b);
	b->current += 6;
	result = ((isc_int64_t)(cp[0])) << 40;
	result |= ((isc_int64_t)(cp[1])) << 32;
	result |= ((isc_int64_t)(cp[2])) << 24;
	result |= ((isc_int64_t)(cp[3])) << 16;
	result |= ((isc_int64_t)(cp[4])) << 8;
	result |= ((isc_int64_t)(cp[5]));

	return (result);
}