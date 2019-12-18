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
 int /*<<< orphan*/  cl_assert (int) ; 
 int git_oid_ncmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  id ; 
 int /*<<< orphan*/  idp ; 

void test_core_oid__ncmp(void)
{
	cl_assert(!git_oid_ncmp(&id, &idp, 0));
	cl_assert(!git_oid_ncmp(&id, &idp, 1));
	cl_assert(!git_oid_ncmp(&id, &idp, 2));
	cl_assert(!git_oid_ncmp(&id, &idp, 17));
	cl_assert(!git_oid_ncmp(&id, &idp, 18));
	cl_assert(git_oid_ncmp(&id, &idp, 19));
	cl_assert(git_oid_ncmp(&id, &idp, 40));
	cl_assert(git_oid_ncmp(&id, &idp, 41));
	cl_assert(git_oid_ncmp(&id, &idp, 42));

	cl_assert(!git_oid_ncmp(&id, &id, 0));
	cl_assert(!git_oid_ncmp(&id, &id, 1));
	cl_assert(!git_oid_ncmp(&id, &id, 39));
	cl_assert(!git_oid_ncmp(&id, &id, 40));
	cl_assert(!git_oid_ncmp(&id, &id, 41));
}