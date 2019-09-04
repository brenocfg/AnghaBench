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
struct ofs_delta_entry {size_t obj_no; int /*<<< orphan*/  offset; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  enum object_type { ____Placeholder_object_type } object_type ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int compare_ofs_delta_bases (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nr_ofs_deltas ; 
 TYPE_1__* objects ; 
 struct ofs_delta_entry* ofs_deltas ; 

__attribute__((used)) static int find_ofs_delta(const off_t offset, enum object_type type)
{
	int first = 0, last = nr_ofs_deltas;

	while (first < last) {
		int next = first + (last - first) / 2;
		struct ofs_delta_entry *delta = &ofs_deltas[next];
		int cmp;

		cmp = compare_ofs_delta_bases(offset, delta->offset,
					      type, objects[delta->obj_no].type);
		if (!cmp)
			return next;
		if (cmp < 0) {
			last = next;
			continue;
		}
		first = next+1;
	}
	return -first-1;
}