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
typedef  unsigned int isc_uint32_t ;
struct TYPE_5__ {int used; int current; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 unsigned char* isc_buffer_current (TYPE_1__*) ; 

isc_uint32_t
isc_buffer_getuint32(isc_buffer_t *b) {
	unsigned char *cp;
	isc_uint32_t result;

	/*
	 * Read an unsigned 32-bit integer in network byte order from 'b',
	 * convert it to host byte order, and return it.
	 */

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(b->used - b->current >= 4);

	cp = isc_buffer_current(b);
	b->current += 4;
	result = ((unsigned int)(cp[0])) << 24;
	result |= ((unsigned int)(cp[1])) << 16;
	result |= ((unsigned int)(cp[2])) << 8;
	result |= ((unsigned int)(cp[3]));

	return (result);
}