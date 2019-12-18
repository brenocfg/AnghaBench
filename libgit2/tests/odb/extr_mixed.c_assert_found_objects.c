#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_10__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
struct TYPE_11__ {int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_odb_expand_id ;
typedef  size_t git_object_t ;
struct TYPE_12__ {size_t expected_type; scalar_t__ expected_id; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_5__*) ; 
 size_t GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_5__* expand_id_test_data ; 
 int /*<<< orphan*/  git_oid_fromstr (TYPE_2__*,scalar_t__) ; 

__attribute__((used)) static void assert_found_objects(git_odb_expand_id *ids)
{
	size_t num, i;

	num = ARRAY_SIZE(expand_id_test_data);

	for (i = 0; i < num; i++) {
		git_oid expected_id = {{0}};
		size_t expected_len = 0;
		git_object_t expected_type = 0;

		if (expand_id_test_data[i].expected_id) {
			git_oid_fromstr(&expected_id, expand_id_test_data[i].expected_id);
			expected_len = GIT_OID_HEXSZ;
			expected_type = expand_id_test_data[i].expected_type;
		}

		cl_assert_equal_oid(&expected_id, &ids[i].id);
		cl_assert_equal_i(expected_len, ids[i].length);
		cl_assert_equal_i(expected_type, ids[i].type);
	}
}