#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; char* member_1; int /*<<< orphan*/ * username; } ;
typedef  TYPE_1__ git_cred_userpass_payload ;
typedef  int /*<<< orphan*/  git_cred ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cred_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_cred_get_username (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_cred_userpass (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 

void test_network_cred__stock_userpass_properly_handles_username_in_url(void)
{
	git_cred *cred;
	git_cred_userpass_payload payload = {"alice", "password"};

	cl_git_pass(git_cred_userpass(&cred, NULL, NULL, GIT_CREDTYPE_USERPASS_PLAINTEXT, &payload));
	cl_assert_equal_s("alice", git_cred_get_username(cred));
	git_cred_free(cred);

	cl_git_pass(git_cred_userpass(&cred, NULL, "bob", GIT_CREDTYPE_USERPASS_PLAINTEXT, &payload));
	cl_assert_equal_s("alice", git_cred_get_username(cred));
	git_cred_free(cred);

	payload.username = NULL;
	cl_git_pass(git_cred_userpass(&cred, NULL, "bob", GIT_CREDTYPE_USERPASS_PLAINTEXT, &payload));
	cl_assert_equal_s("bob", git_cred_get_username(cred));
	git_cred_free(cred);
}