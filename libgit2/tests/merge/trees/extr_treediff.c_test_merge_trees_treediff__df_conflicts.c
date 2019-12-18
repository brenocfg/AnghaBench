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
struct TYPE_9__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_8__ {int /*<<< orphan*/  member_1; TYPE_3__ member_0; } ;
struct TYPE_7__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_1; TYPE_1__ member_0; } ;
struct TYPE_11__ {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
struct TYPE_10__ {int /*<<< orphan*/  member_1; TYPE_5__ member_0; } ;
struct merge_index_conflict_data {int /*<<< orphan*/  member_3; TYPE_2__ member_2; TYPE_6__ member_1; TYPE_4__ member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_ADDED ; 
 int /*<<< orphan*/  GIT_DELTA_DELETED ; 
 int /*<<< orphan*/  GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  GIT_DELTA_UNMODIFIED ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_BOTH_ADDED ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_BOTH_DELETED ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_DF_CHILD ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_DIRECTORY_FILE ; 
 int /*<<< orphan*/  GIT_MERGE_DIFF_NONE ; 
 int /*<<< orphan*/  TREE_OID_DF_ANCESTOR ; 
 int /*<<< orphan*/  TREE_OID_DF_SIDE1 ; 
 int /*<<< orphan*/  TREE_OID_DF_SIDE2 ; 
 int /*<<< orphan*/  test_find_differences (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct merge_index_conflict_data*,int) ; 

void test_merge_trees_treediff__df_conflicts(void)
{
	struct merge_index_conflict_data treediff_conflict_data[] = {
		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "49130a28ef567af9a6a6104c38773fedfa5f9742", 0, "dir-10" }, GIT_DELTA_ADDED },
			{ { 0100644, "6c06dcd163587c2cc18be44857e0b71116382aeb", 0, "dir-10" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_BOTH_ADDED,
		},

		{
			{ { 0100644, "242591eb280ee9eeb2ce63524b9a8b9bc4cb515d", 0, "dir-10/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_BOTH_DELETED,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "43aafd43bea779ec74317dc361f45ae3f532a505", 0, "dir-6" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "cf8c5cc8a85a1ff5a4ba51e0bc7cf5665669924d", 0, "dir-6/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "cf8c5cc8a85a1ff5a4ba51e0bc7cf5665669924d", 0, "dir-6/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "a031a28ae70e33a641ce4b8a8f6317f1ab79dee4", 0, "dir-7" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_DIRECTORY_FILE,
		},

		{
			{ { 0100644, "5012fd565b1393bdfda1805d4ec38ce6619e1fd1", 0, "dir-7/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "a5563304ddf6caba25cb50323a2ea6f7dbfcadca", 0, "dir-7/file.txt" }, GIT_DELTA_MODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_DF_CHILD,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "e9ad6ec3e38364a3d07feda7c4197d4d845c53b5", 0, "dir-8" }, GIT_DELTA_ADDED },
			{ {0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "f20c9063fa0bda9a397c96947a7b687305c49753", 0, "dir-8/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0100644, "f20c9063fa0bda9a397c96947a7b687305c49753", 0, "dir-8/file.txt" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "3ef4d30382ca33fdeba9fda895a99e0891ba37aa", 0, "dir-9" }, GIT_DELTA_ADDED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_DIRECTORY_FILE,
		},

		{
			{ { 0100644, "fc4c636d6515e9e261f9260dbcf3cc6eca97ea08", 0, "dir-9/file.txt" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0100644, "76ab0e2868197ec158ddd6c78d8a0d2fd73d38f9", 0, "dir-9/file.txt" }, GIT_DELTA_MODIFIED },
			GIT_MERGE_DIFF_DF_CHILD,
		},

		{
			{ { 0100644, "1e4ff029aee68d0d69ef9eb6efa6cbf1ec732f99", 0, "file-1" },  GIT_DELTA_UNMODIFIED },
			{ { 0100644, "1e4ff029aee68d0d69ef9eb6efa6cbf1ec732f99", 0, "file-1" },  GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "5c2411f8075f48a6b2fdb85ebc0d371747c4df15", 0, "file-1/new" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "a39a620dae5bc8b4e771cd4d251b7d080401a21e", 0, "file-2" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "d963979c237d08b6ba39062ee7bf64c7d34a27f8", 0, "file-2" }, GIT_DELTA_MODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_DIRECTORY_FILE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "5c341ead2ba6f2af98ce5ec3fe84f6b6d2899c0d", 0, "file-2/new" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_DF_CHILD,
		},

		{
			{ { 0100644, "032ebc5ab85d9553bb187d3cd40875ff23a63ed0", 0, "file-3" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0100644, "032ebc5ab85d9553bb187d3cd40875ff23a63ed0", 0, "file-3" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "9efe7723802d4305142eee177e018fee1572c4f4", 0, "file-3/new" }, GIT_DELTA_ADDED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_NONE,
		},

		{
			{ { 0100644, "bacac9b3493509aa15e1730e1545fc0919d1dae0", 0, "file-4" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0100644, "7663fce0130db092936b137cabd693ec234eb060", 0, "file-4" }, GIT_DELTA_MODIFIED },
			GIT_MERGE_DIFF_DIRECTORY_FILE,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "e49f917b448d1340b31d76e54ba388268fd4c922", 0, "file-4/new" }, GIT_DELTA_ADDED },
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			GIT_MERGE_DIFF_DF_CHILD,
		},

		{
			{ { 0100644, "ac4045f965119e6998f4340ed0f411decfb3ec05", 0, "file-5" }, GIT_DELTA_UNMODIFIED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			{ { 0, "", 0, "" }, GIT_DELTA_DELETED },
			GIT_MERGE_DIFF_BOTH_DELETED,
		},

		{
			{ { 0, "", 0, "" }, GIT_DELTA_UNMODIFIED },
			{ { 0100644, "cab2cf23998b40f1af2d9d9a756dc9e285a8df4b", 0, "file-5/new" }, GIT_DELTA_ADDED },
			{ { 0100644, "f5504f36e6f4eb797a56fc5bac6c6c7f32969bf2", 0, "file-5/new" }, GIT_DELTA_ADDED },
			GIT_MERGE_DIFF_BOTH_ADDED,
		},
	};

	test_find_differences(TREE_OID_DF_ANCESTOR, TREE_OID_DF_SIDE1, TREE_OID_DF_SIDE2, treediff_conflict_data, 20);
}