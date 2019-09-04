#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_note ;
typedef  int /*<<< orphan*/  git_blob ;

/* Variables and functions */
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_blob_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_blob_rawcontent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_note_message (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void assert_note_equal(git_note *note, char *message, git_oid *note_oid) {
	git_blob *blob;

	cl_assert_equal_s(git_note_message(note), message);
	cl_assert_equal_oid(git_note_id(note), note_oid);

	cl_git_pass(git_blob_lookup(&blob, _repo, note_oid));
	cl_assert_equal_s(git_note_message(note), (const char *)git_blob_rawcontent(blob));

	git_blob_free(blob);
}