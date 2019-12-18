#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int length; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ isc_region_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int
isc_region_compare(isc_region_t *r1, isc_region_t *r2) {
	unsigned int l;
	int result;

	REQUIRE(r1 != NULL);
	REQUIRE(r2 != NULL);
	       
	l = (r1->length < r2->length) ? r1->length : r2->length;

	if ((result = memcmp(r1->base, r2->base, l)) != 0)
		return ((result < 0) ? -1 : 1);
	else
		return ((r1->length == r2->length) ? 0 :
			(r1->length < r2->length) ? -1 : 1);
}