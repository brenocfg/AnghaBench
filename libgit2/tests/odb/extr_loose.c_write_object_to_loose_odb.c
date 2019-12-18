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
typedef  int /*<<< orphan*/  git_odb_backend ;
typedef  int /*<<< orphan*/  git_odb ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_odb_add_backend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_odb_backend_loose (int /*<<< orphan*/ **,char*,int,int,int,int) ; 
 int /*<<< orphan*/  git_odb_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_odb_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_odb_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void write_object_to_loose_odb(int fsync)
{
	git_odb *odb;
	git_odb_backend *backend;
	git_oid oid;

	cl_git_pass(git_odb_new(&odb));
	cl_git_pass(git_odb_backend_loose(&backend, "test-objects", -1, fsync, 0777, 0666));
	cl_git_pass(git_odb_add_backend(odb, backend, 1));
	cl_git_pass(git_odb_write(&oid, odb, "Test data\n", 10, GIT_OBJECT_BLOB));
	git_odb_free(odb);
}