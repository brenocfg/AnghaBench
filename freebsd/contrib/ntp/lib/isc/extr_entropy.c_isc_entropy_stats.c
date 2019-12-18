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
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_entropy_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_ENTROPY (TYPE_1__*) ; 
 int /*<<< orphan*/  dumpstats (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
isc_entropy_stats(isc_entropy_t *ent, FILE *out) {
	REQUIRE(VALID_ENTROPY(ent));

	LOCK(&ent->lock);
	dumpstats(ent, out);
	UNLOCK(&ent->lock);
}