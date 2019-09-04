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
struct object_id {int dummy; } ;
struct bulk_checkin_state {int nr_written; TYPE_1__** written; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 scalar_t__ has_object_file (struct object_id*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id*) ; 

__attribute__((used)) static int already_written(struct bulk_checkin_state *state, struct object_id *oid)
{
	int i;

	/* The object may already exist in the repository */
	if (has_object_file(oid))
		return 1;

	/* Might want to keep the list sorted */
	for (i = 0; i < state->nr_written; i++)
		if (oideq(&state->written[i]->oid, oid))
			return 1;

	/* This is a new object we need to keep */
	return 0;
}