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
struct sshauthopt {int restricted; scalar_t__ permit_user_rc; scalar_t__ permit_pty_flag; scalar_t__ permit_x11_forwarding_flag; scalar_t__ permit_agent_forwarding_flag; scalar_t__ permit_port_forwarding_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshauthopt*,int /*<<< orphan*/ *) ; 
 struct sshauthopt* sshauthopt_new () ; 

__attribute__((used)) static struct sshauthopt *
default_authkey_restrict_opts(void)
{
	struct sshauthopt *ret = sshauthopt_new();

	ASSERT_PTR_NE(ret, NULL);
	ret->permit_port_forwarding_flag = 0;
	ret->permit_agent_forwarding_flag = 0;
	ret->permit_x11_forwarding_flag = 0;
	ret->permit_pty_flag = 0;
	ret->permit_user_rc = 0;
	ret->restricted = 1;
	return ret;
}