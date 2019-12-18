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

/* Variables and functions */
 int /*<<< orphan*/  _odb ; 
 int /*<<< orphan*/  _oid ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_blob_create_from_buffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__) ; 
 int git_odb_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (char const*) ; 

void test_odb_backend_mempack__blob_create_from_buffer_succeeds(void)
{
	const char *data = "data";

	cl_git_pass(git_blob_create_from_buffer(&_oid, _repo, data, strlen(data) + 1));
	cl_assert(git_odb_exists(_odb, &_oid) == 1);
}