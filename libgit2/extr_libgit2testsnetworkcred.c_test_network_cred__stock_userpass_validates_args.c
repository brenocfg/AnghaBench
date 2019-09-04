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
struct TYPE_3__ {char* username; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_cred_userpass_payload ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_cred_userpass (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

void test_network_cred__stock_userpass_validates_args(void)
{
	git_cred_userpass_payload payload = {0};

	cl_git_fail(git_cred_userpass(NULL, NULL, NULL, 0, NULL));

	payload.username = "user";
	cl_git_fail(git_cred_userpass(NULL, NULL, NULL, 0, &payload));

	payload.username = NULL;
	payload.username = "pass";
	cl_git_fail(git_cred_userpass(NULL, NULL, NULL, 0, &payload));
}