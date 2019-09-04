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
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/  dlen; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ object_data ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_odb ;
typedef  int /*<<< orphan*/  git_object_t ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_string2type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_odb_read_header (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_object_files (TYPE_1__*) ; 

__attribute__((used)) static void test_read_header(object_data *data)
{
	git_oid id;
	git_odb *odb;
	size_t len;
	git_object_t type;

	write_object_files(data);

	cl_git_pass(git_odb_open(&odb, "test-objects"));
	cl_git_pass(git_oid_fromstr(&id, data->id));
	cl_git_pass(git_odb_read_header(&len, &type, odb, &id));

	cl_assert_equal_sz(data->dlen, len);
	cl_assert_equal_i(git_object_string2type(data->type), type);

	git_odb_free(odb);
}