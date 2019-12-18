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
typedef  int /*<<< orphan*/  isc_uint32_t ;
struct TYPE_5__ {scalar_t__ initialized; int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ isc_entropy_t ;

/* Variables and functions */
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 scalar_t__ THRESHOLD_BITS ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VALID_ENTROPY (TYPE_1__*) ; 
 int /*<<< orphan*/  entropypool_adddata (TYPE_1__*,void*,unsigned int,int /*<<< orphan*/ ) ; 

void
isc_entropy_putdata(isc_entropy_t *ent, void *data, unsigned int length,
		    isc_uint32_t entropy)
{
	REQUIRE(VALID_ENTROPY(ent));

	LOCK(&ent->lock);

	entropypool_adddata(ent, data, length, entropy);

	if (ent->initialized < THRESHOLD_BITS)
		ent->initialized = THRESHOLD_BITS;

	UNLOCK(&ent->lock);
}