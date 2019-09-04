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
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int find_ref_delta (struct object_id const*,int) ; 
 int nr_ref_deltas ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,struct object_id const*) ; 
 TYPE_1__* ref_deltas ; 

__attribute__((used)) static void find_ref_delta_children(const struct object_id *oid,
				    int *first_index, int *last_index,
				    enum object_type type)
{
	int first = find_ref_delta(oid, type);
	int last = first;
	int end = nr_ref_deltas - 1;

	if (first < 0) {
		*first_index = 0;
		*last_index = -1;
		return;
	}
	while (first > 0 && oideq(&ref_deltas[first - 1].oid, oid))
		--first;
	while (last < end && oideq(&ref_deltas[last + 1].oid, oid))
		++last;
	*first_index = first;
	*last_index = last;
}