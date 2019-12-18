#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct opts {int /*<<< orphan*/  diffopts; int /*<<< orphan*/ * treeish2; int /*<<< orphan*/ * treeish1; } ;
typedef  int /*<<< orphan*/  git_patch ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_4__ {int /*<<< orphan*/  size; int /*<<< orphan*/  ptr; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  check_lg2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_buffers (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_to_buf (TYPE_1__*,int /*<<< orphan*/ *) ; 
 char* read_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  usage (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void compute_diff_no_index(git_diff **diff, struct opts *o) {
	git_patch *patch = NULL;
	char *file1_str = NULL;
	char *file2_str = NULL;
	git_buf buf = {0};

	if (!o->treeish1 || !o->treeish2) {
		usage("two files should be provided as arguments", NULL);
	}
	file1_str = read_file(o->treeish1);
	if (file1_str == NULL) {
		usage("file cannot be read", o->treeish1);
	}
	file2_str = read_file(o->treeish2);
	if (file2_str == NULL) {
		usage("file cannot be read", o->treeish2);
	}
	check_lg2(
		git_patch_from_buffers(&patch, file1_str, strlen(file1_str), o->treeish1, file2_str, strlen(file2_str), o->treeish2, &o->diffopts),
		"patch buffers", NULL);
	check_lg2(
		git_patch_to_buf(&buf, patch),
		"patch to buf", NULL);
	check_lg2(
		git_diff_from_buffer(diff, buf.ptr, buf.size),
		"diff from patch", NULL);
	git_patch_free(patch);
	git_buf_dispose(&buf);
	free(file1_str);
	free(file2_str);
}