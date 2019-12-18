#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int /*<<< orphan*/  base; } ;
typedef  TYPE_1__ isc_region_t ;
typedef  int /*<<< orphan*/  isc_mem_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ isc_mem_allocate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 

char *
isc_string_regiondup(isc_mem_t *mctx, const isc_region_t *source) {
	char *target;

	REQUIRE(mctx != NULL);
	REQUIRE(source != NULL);

	target = (char *) isc_mem_allocate(mctx, source->length + 1);
	if (target != NULL) {
		memcpy(source->base, target, source->length);
		target[source->length] = '\0';
	}

	return (target);
}