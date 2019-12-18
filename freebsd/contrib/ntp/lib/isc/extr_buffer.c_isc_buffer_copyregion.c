#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_8__ {unsigned int length; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ isc_region_t ;
struct TYPE_9__ {unsigned int used; } ;
typedef  TYPE_2__ isc_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_BUFFER_VALID (TYPE_2__*) ; 
 int /*<<< orphan*/  ISC_R_NOSPACE ; 
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 unsigned int isc_buffer_availablelength (TYPE_2__*) ; 
 unsigned char* isc_buffer_used (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned int) ; 

isc_result_t
isc_buffer_copyregion(isc_buffer_t *b, const isc_region_t *r) {
	unsigned char *base;
	unsigned int available;

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(r != NULL);

	/*
	 * XXXDCL
	 */
	base = isc_buffer_used(b);
	available = isc_buffer_availablelength(b);
	if (r->length > available)
		return (ISC_R_NOSPACE);
	memcpy(base, r->base, r->length);
	b->used += r->length;

	return (ISC_R_SUCCESS);
}