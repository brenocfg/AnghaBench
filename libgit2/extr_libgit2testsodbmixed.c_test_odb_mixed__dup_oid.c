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
typedef  int /*<<< orphan*/  short_hex ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb_object ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_exists_prefix (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_read_prefix (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_oid_fromstrn (int /*<<< orphan*/ *,char const*,int) ; 

void test_odb_mixed__dup_oid(void) {
	const char hex[] = "ce013625030ba8dba906f756967f9e9ca394464a";
	const char short_hex[] = "ce01362";
	git_oid oid;
	git_odb_object *obj;

	cl_git_pass(git_oid_fromstr(&oid, hex));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, GIT_OID_HEXSZ));
	git_odb_object_free(obj);

	cl_git_pass(git_odb_exists_prefix(NULL, _odb, &oid, GIT_OID_HEXSZ));

	cl_git_pass(git_oid_fromstrn(&oid, short_hex, sizeof(short_hex) - 1));
	cl_git_pass(git_odb_read_prefix(&obj, _odb, &oid, sizeof(short_hex) - 1));
	git_odb_object_free(obj);

	cl_git_pass(git_odb_exists_prefix(NULL, _odb, &oid, sizeof(short_hex) - 1));
}