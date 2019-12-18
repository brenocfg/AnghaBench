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
struct TYPE_4__ {scalar_t__ refs; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_ratelimiter_t ;

/* Variables and functions */
 int /*<<< orphan*/  INSIST (int) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 

void
isc_ratelimiter_attach(isc_ratelimiter_t *source, isc_ratelimiter_t **target) {
	REQUIRE(source != NULL);
	REQUIRE(target != NULL && *target == NULL);

	LOCK(&source->lock);
	REQUIRE(source->refs > 0);
	source->refs++;
	INSIST(source->refs > 0);
	UNLOCK(&source->lock);
	*target = source;
}