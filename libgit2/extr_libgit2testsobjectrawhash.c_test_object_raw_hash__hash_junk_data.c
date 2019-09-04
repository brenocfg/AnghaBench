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
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int type; int len; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int GIT_OBJECT_BLOB ; 
 int GIT_OBJECT_OFS_DELTA ; 
 int GIT_OBJECT_REF_DELTA ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_object_fail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  hash_object_pass (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ junk_obj ; 
 int /*<<< orphan*/ * some_data ; 
 int /*<<< orphan*/  zero_id ; 

void test_object_raw_hash__hash_junk_data(void)
{
	git_oid id, id_zero;

	cl_git_pass(git_oid_fromstr(&id_zero, zero_id));

	/* invalid types: */
	junk_obj.data = some_data;
	hash_object_fail(&id, &junk_obj);

	junk_obj.type = 0; /* EXT1 */
	hash_object_fail(&id, &junk_obj);

	junk_obj.type = 5; /* EXT2 */
	hash_object_fail(&id, &junk_obj);

	junk_obj.type = GIT_OBJECT_OFS_DELTA;
	hash_object_fail(&id, &junk_obj);

	junk_obj.type = GIT_OBJECT_REF_DELTA;
	hash_object_fail(&id, &junk_obj);

	junk_obj.type = 42;
	hash_object_fail(&id, &junk_obj);

	/* data can be NULL only if len is zero: */
	junk_obj.type = GIT_OBJECT_BLOB;
	junk_obj.data = NULL;
	hash_object_pass(&id, &junk_obj);
	cl_assert(git_oid_cmp(&id, &id_zero) == 0);

	junk_obj.len = 1;
	hash_object_fail(&id, &junk_obj);
}