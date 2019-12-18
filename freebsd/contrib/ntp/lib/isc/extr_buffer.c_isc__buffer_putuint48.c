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
typedef  int isc_uint64_t ;
typedef  scalar_t__ isc_uint32_t ;
typedef  scalar_t__ isc_uint16_t ;
struct TYPE_6__ {scalar_t__ used; scalar_t__ length; } ;
typedef  TYPE_1__ isc_buffer_t ;

/* Variables and functions */
 int ISC_BUFFER_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  ISC__BUFFER_PUTUINT16 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  ISC__BUFFER_PUTUINT32 (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 

void
isc__buffer_putuint48(isc_buffer_t *b, isc_uint64_t val) {
	isc_uint16_t valhi;
	isc_uint32_t vallo;

	REQUIRE(ISC_BUFFER_VALID(b));
	REQUIRE(b->used + 6 <= b->length);

	valhi = (isc_uint16_t)(val >> 32);
	vallo = (isc_uint32_t)(val & 0xFFFFFFFF);
	ISC__BUFFER_PUTUINT16(b, valhi);
	ISC__BUFFER_PUTUINT32(b, vallo);
}