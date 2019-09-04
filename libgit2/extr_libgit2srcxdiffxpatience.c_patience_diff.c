#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xpparam_t ;
struct TYPE_7__ {int* rchg; } ;
struct TYPE_6__ {int* rchg; } ;
struct TYPE_8__ {TYPE_2__ xdf2; TYPE_1__ xdf1; } ;
typedef  TYPE_3__ xdfenv_t ;
struct hashmap {int /*<<< orphan*/  entries; int /*<<< orphan*/  has_matches; } ;
struct entry {int dummy; } ;
typedef  int /*<<< orphan*/  mmfile_t ;
typedef  int /*<<< orphan*/  map ;

/* Variables and functions */
 int fall_back_to_classic_diff (struct hashmap*,int,int,int,int) ; 
 scalar_t__ fill_hashmap (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_3__*,struct hashmap*,int,int,int,int) ; 
 struct entry* find_longest_common_sequence (struct hashmap*) ; 
 int /*<<< orphan*/  memset (struct hashmap*,int /*<<< orphan*/ ,int) ; 
 int walk_common_sequence (struct hashmap*,struct entry*,int,int,int,int) ; 
 int /*<<< orphan*/  xdl_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int patience_diff(mmfile_t *file1, mmfile_t *file2,
		xpparam_t const *xpp, xdfenv_t *env,
		int line1, int count1, int line2, int count2)
{
	struct hashmap map;
	struct entry *first;
	int result = 0;

	/* trivial case: one side is empty */
	if (!count1) {
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		return 0;
	} else if (!count2) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		return 0;
	}

	memset(&map, 0, sizeof(map));
	if (fill_hashmap(file1, file2, xpp, env, &map,
			line1, count1, line2, count2))
		return -1;

	/* are there any matching lines at all? */
	if (!map.has_matches) {
		while(count1--)
			env->xdf1.rchg[line1++ - 1] = 1;
		while(count2--)
			env->xdf2.rchg[line2++ - 1] = 1;
		xdl_free(map.entries);
		return 0;
	}

	first = find_longest_common_sequence(&map);
	if (first)
		result = walk_common_sequence(&map, first,
			line1, count1, line2, count2);
	else
		result = fall_back_to_classic_diff(&map,
			line1, count1, line2, count2);

	xdl_free(map.entries);
	return result;
}