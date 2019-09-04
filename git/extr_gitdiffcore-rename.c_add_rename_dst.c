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
struct diff_filespec {int /*<<< orphan*/  mode; int /*<<< orphan*/  oid_valid; int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct TYPE_5__ {int /*<<< orphan*/ * pair; int /*<<< orphan*/  two; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MOVE_ARRAY (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  alloc_filespec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_filespec (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int find_rename_dst (struct diff_filespec*) ; 
 TYPE_1__* rename_dst ; 
 int /*<<< orphan*/  rename_dst_alloc ; 
 int rename_dst_nr ; 

__attribute__((used)) static int add_rename_dst(struct diff_filespec *two)
{
	int first = find_rename_dst(two);

	if (first >= 0)
		return -1;
	first = -first - 1;

	/* insert to make it at "first" */
	ALLOC_GROW(rename_dst, rename_dst_nr + 1, rename_dst_alloc);
	rename_dst_nr++;
	if (first < rename_dst_nr)
		MOVE_ARRAY(rename_dst + first + 1, rename_dst + first,
			   rename_dst_nr - first - 1);
	rename_dst[first].two = alloc_filespec(two->path);
	fill_filespec(rename_dst[first].two, &two->oid, two->oid_valid,
		      two->mode);
	rename_dst[first].pair = NULL;
	return 0;
}