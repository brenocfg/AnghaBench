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
struct TYPE_2__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_TYPECHANGE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ expect ; 
 int /*<<< orphan*/  process_tree_to_tree_diffing (char*,char*) ; 

void test_diff_tree__symlink_blob_mode_changed_to_regular_file(void)
{
	/*
	* $ git diff  7fccd7..806999
	* diff --git a/include/Nu/Nu.h b/include/Nu/Nu.h
	* deleted file mode 120000
	* index 19bf568..0000000
	* --- a/include/Nu/Nu.h
	* +++ /dev/null
	* @@ -1 +0,0 @@
	* -../../objc/Nu.h
	* \ No newline at end of file
	* diff --git a/include/Nu/Nu.h b/include/Nu/Nu.h
	* new file mode 100644
	* index 0000000..f9e6561
	* --- /dev/null
	* +++ b/include/Nu/Nu.h
	* @@ -0,0 +1 @@
	* +awesome content
	* diff --git a/objc/Nu.h b/objc/Nu.h
	* deleted file mode 100644
	* index f9e6561..0000000
	* --- a/objc/Nu.h
	* +++ /dev/null
	* @@ -1 +0,0 @@
	* -awesome content
	*/

	process_tree_to_tree_diffing("7fccd7", "806999");

	cl_assert_equal_i(3, expect.files);
	cl_assert_equal_i(2, expect.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(0, expect.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(1, expect.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(0, expect.file_status[GIT_DELTA_TYPECHANGE]);
}