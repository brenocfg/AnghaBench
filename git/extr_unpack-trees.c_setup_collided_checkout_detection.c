#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct checkout {int clone; } ;
struct TYPE_2__ {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_MATCHED ; 

__attribute__((used)) static void setup_collided_checkout_detection(struct checkout *state,
					      struct index_state *index)
{
	int i;

	state->clone = 1;
	for (i = 0; i < index->cache_nr; i++)
		index->cache[i]->ce_flags &= ~CE_MATCHED;
}