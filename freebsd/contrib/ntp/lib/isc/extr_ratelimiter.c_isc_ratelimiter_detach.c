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
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 scalar_t__ ISC_FALSE ; 
 scalar_t__ ISC_TRUE ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ratelimiter_free (TYPE_1__*) ; 

void
isc_ratelimiter_detach(isc_ratelimiter_t **rlp) {
	isc_ratelimiter_t *rl = *rlp;
	isc_boolean_t free_now = ISC_FALSE;

	LOCK(&rl->lock);
	REQUIRE(rl->refs > 0);
	rl->refs--;
	if (rl->refs == 0)
		free_now = ISC_TRUE;
	UNLOCK(&rl->lock);

	if (free_now)
		ratelimiter_free(rl);

	*rlp = NULL;
}