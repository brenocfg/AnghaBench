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
typedef  scalar_t__ u_int ;
struct TYPE_6__ {int /*<<< orphan*/  used; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 size_t isc_buffer_availablelength (TYPE_1__*) ; 
 unsigned char* isc_buffer_used (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

void
isc__buffer_putstr(isc_buffer_t *b, const char *source) {
	size_t l;
	unsigned char *cp;

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(source != NULL);

	/*
	 * Do not use ISC__BUFFER_PUTSTR(), so strlen is only done once.
	 */
	l = strlen(source);

	REQUIRE(l <= isc_buffer_availablelength(b));

	cp = isc_buffer_used(b);
	memcpy(cp, source, l);
	b->used += (u_int)l; /* checked above - no overflow here */
}