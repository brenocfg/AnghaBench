#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* ent; } ;
typedef  TYPE_1__ isc_entropysource_t ;
struct TYPE_10__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ isc_entropy_t ;
typedef  scalar_t__ isc_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_ENTROPY (TYPE_2__*) ; 
 int /*<<< orphan*/  VALID_SOURCE (TYPE_1__*) ; 
 int /*<<< orphan*/  destroy (TYPE_2__**) ; 
 scalar_t__ destroy_check (TYPE_2__*) ; 
 int /*<<< orphan*/  destroysource (TYPE_1__**) ; 

void
isc_entropy_destroysource(isc_entropysource_t **sourcep) {
	isc_entropysource_t *source;
	isc_entropy_t *ent;
	isc_boolean_t killit;

	REQUIRE(sourcep != NULL);
	REQUIRE(VALID_SOURCE(*sourcep));

	source = *sourcep;
	*sourcep = NULL;

	ent = source->ent;
	REQUIRE(VALID_ENTROPY(ent));

	LOCK(&ent->lock);

	destroysource(&source);

	killit = destroy_check(ent);

	UNLOCK(&ent->lock);

	if (killit)
		destroy(&ent);
}