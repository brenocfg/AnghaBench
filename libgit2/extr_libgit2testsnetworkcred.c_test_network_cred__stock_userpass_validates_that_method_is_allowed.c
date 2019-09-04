#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* member_0; char* member_1; } ;
typedef  TYPE_1__ git_cred_userpass_payload ;
struct TYPE_7__ {int /*<<< orphan*/  (* free ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ git_cred ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CREDTYPE_USERPASS_PLAINTEXT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cred_userpass (TYPE_2__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void test_network_cred__stock_userpass_validates_that_method_is_allowed(void)
{
	git_cred *cred;
	git_cred_userpass_payload payload = {"user", "pass"};

	cl_git_fail(git_cred_userpass(&cred, NULL, NULL, 0, &payload));
	cl_git_pass(git_cred_userpass(&cred, NULL, NULL, GIT_CREDTYPE_USERPASS_PLAINTEXT, &payload));
	cred->free(cred);
}