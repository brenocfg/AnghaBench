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
typedef  int /*<<< orphan*/  isc_result_t ;
struct TYPE_3__ {unsigned int refs; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_refcount_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_R_SUCCESS ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_mutex_init (int /*<<< orphan*/ *) ; 

isc_result_t
isc_refcount_init(isc_refcount_t *ref, unsigned int n) {
	REQUIRE(ref != NULL);

	ref->refs = n;
#if defined(ISC_PLATFORM_USETHREADS) && !defined(ISC_PLATFORM_HAVEXADD)
	return (isc_mutex_init(&ref->lock));
#else
	return (ISC_R_SUCCESS);
#endif
}