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
typedef  scalar_t__ off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {scalar_t__ offset; } ;

/* Variables and functions */
 int find_ofs_delta (scalar_t__,int) ; 
 int nr_ofs_deltas ; 
 TYPE_1__* ofs_deltas ; 

__attribute__((used)) static void find_ofs_delta_children(off_t offset,
				    int *first_index, int *last_index,
				    enum object_type type)
{
	int first = find_ofs_delta(offset, type);
	int last = first;
	int end = nr_ofs_deltas - 1;

	if (first < 0) {
		*first_index = 0;
		*last_index = -1;
		return;
	}
	while (first > 0 && ofs_deltas[first - 1].offset == offset)
		--first;
	while (last < end && ofs_deltas[last + 1].offset == offset)
		++last;
	*first_index = first;
	*last_index = last;
}