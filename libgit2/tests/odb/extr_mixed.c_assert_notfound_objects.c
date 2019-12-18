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
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
struct TYPE_8__ {int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ git_odb_expand_id ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expand_id_test_data ; 

__attribute__((used)) static void assert_notfound_objects(git_odb_expand_id *ids)
{
	git_oid expected_id = {{0}};
	size_t num, i;

	num = ARRAY_SIZE(expand_id_test_data);

	for (i = 0; i < num; i++) {
		cl_assert_equal_oid(&expected_id, &ids[i].id);
		cl_assert_equal_i(0, ids[i].length);
		cl_assert_equal_i(0, ids[i].type);
	}
}