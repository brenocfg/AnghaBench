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
struct TYPE_5__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int VALID_ENTROPY (TYPE_1__*) ; 

void
isc_entropy_attach(isc_entropy_t *ent, isc_entropy_t **entp) {
	REQUIRE(VALID_ENTROPY(ent));
	REQUIRE(entp != NULL && *entp == NULL);

	LOCK(&ent->lock);

	ent->refcnt++;
	*entp = ent;

	UNLOCK(&ent->lock);
}