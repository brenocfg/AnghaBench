#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_1; TYPE_6__ member_0; } ;
struct TYPE_10__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_9__ {int /*<<< orphan*/  member_1; TYPE_4__ member_0; } ;
struct TYPE_8__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_7__ {int /*<<< orphan*/  member_1; TYPE_2__ member_0; } ;
struct merge_index_conflict_data {int /*<<< orphan*/  member_3; TYPE_5__ member_2; TYPE_3__ member_1; TYPE_1__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_ADDED ; 
 int /*<<< orphan*/  GIT_DELTA_DELETED ; 
 int /*<<< orphan*/  GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  GIT_DELTA_RENAMED ; 
 int /*<<< orphan*/  GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_NONE ; 
 int /*<<< orphan*/  TREE_OID_ANCESTOR ; 
 int /*<<< orphan*/  TREE_OID_MASTER ; 
 int /*<<< orphan*/  TREE_OID_RENAMES1 ; 
 int /*<<< orphan*/  test_find_differences (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct merge_index_conflict_data*,int) ; 

void test_merge_trees_treediff__strict_renames(void)
{
	struct merge_index_conflict_data treediff_conflict_data[] = {
		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "233c0919c998ed110a4b6ff36f353aec8b713487", 0, "added-in-master.txt" }, GIT_DELTA_ADDED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "6212c31dab5e482247d7977e4f0dd3601decf13b", 0, "automergeable.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf", 0, "automergeable.txt" }, GIT_DELTA_MODIFIED },
			{ { 0100644, "6212c31dab5e482247d7977e4f0dd3601decf13b", 0, "automergeable.txt" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "ab6c44a2e84492ad4b41bb6bac87353e9d02ac8b", 0, "changed-in-master.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "11deab00b2d3a6f5a3073988ac050c2d7b6655e2", 0, "changed-in-master.txt" }, GIT_DELTA_MODIFIED },
			{ { 0100644, "ab6c44a2e84492ad4b41bb6bac87353e9d02ac8b", 0, "changed-in-master.txt" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "d427e0b2e138501a3d15cc376077a3631e15bd46", 0, "conflicting.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "4e886e602529caa9ab11d71f86634bd1b6e0de10", 0, "conflicting.txt" }, GIT_DELTA_MODIFIED },
			{ { 0100644, "d427e0b2e138501a3d15cc376077a3631e15bd46", 0, "conflicting.txt" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "dfe3f22baa1f6fce5447901c3086bae368de6bdd", 0, "removed-in-branch.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "dfe3f22baa1f6fce5447901c3086bae368de6bdd", 0, "removed-in-branch.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "dfe3f22baa1f6fce5447901c3086bae368de6bdd", 0, "renamed-in-branch.txt" }, GIT_DELTA_RENAMED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "5c3b68a71fc4fa5d362fd3875e53137c6a5ab7a5", 0, "removed-in-master.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0100644,  "5c3b68a71fc4fa5d362fd3875e53137c6a5ab7a5", 0, "removed-in-master.txt" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "c8f06f2e3bb2964174677e91f0abead0e43c9e5d", 0, "renamed.txt" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "c8f06f2e3bb2964174677e91f0abead0e43c9e5d", 0, "unchanged.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "c8f06f2e3bb2964174677e91f0abead0e43c9e5d", 0, "unchanged.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "c8f06f2e3bb2964174677e91f0abead0e43c9e5d", 0, "copied.txt" }, GIT_DELTA_RENAMED },
			GIT_MERGE_DIFF_NONE,
		},
    };

	test_find_differences(TREE_OID_ANCESTOR, TREE_OID_MASTER, TREE_OID_RENAMES1, treediff_conflict_data, 8);
}