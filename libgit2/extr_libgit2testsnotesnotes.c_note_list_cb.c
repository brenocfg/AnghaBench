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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_2__ {int /*<<< orphan*/  annotated_object_sha; int /*<<< orphan*/  note_sha; } ;

/* Variables and functions */
 unsigned int EXPECTATIONS_COUNT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* list_expectations ; 

__attribute__((used)) static int note_list_cb(
	const git_oid *blob_id, const git_oid *annotated_obj_id, void *payload)
{
	git_oid expected_note_oid, expected_target_oid;

	unsigned int *count = (unsigned int *)payload;

	cl_assert(*count < EXPECTATIONS_COUNT);

	cl_git_pass(git_oid_fromstr(&expected_note_oid, list_expectations[*count].note_sha));
	cl_assert_equal_oid(&expected_note_oid, blob_id);

	cl_git_pass(git_oid_fromstr(&expected_target_oid, list_expectations[*count].annotated_object_sha));
	cl_assert_equal_oid(&expected_target_oid, annotated_obj_id);

	(*count)++;

	return 0;
}