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
 int /*<<< orphan*/  EXISTING_HASH ; 
 int /*<<< orphan*/  NONEXISTING_HASH ; 
 int /*<<< orphan*/  _existing_oid ; 
 int /*<<< orphan*/  _nonexisting_oid ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_repository_and_backend () ; 

void test_odb_backend_nonrefreshing__initialize(void)
{
	git_oid_fromstr(&_nonexisting_oid, NONEXISTING_HASH);
	git_oid_fromstr(&_existing_oid, EXISTING_HASH);
	setup_repository_and_backend();
}