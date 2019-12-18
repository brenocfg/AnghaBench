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
struct sshauthopt {int permit_port_forwarding_flag; int permit_agent_forwarding_flag; int permit_x11_forwarding_flag; int permit_pty_flag; int permit_user_rc; } ;

/* Variables and functions */
 struct sshauthopt* sshauthopt_new () ; 

struct sshauthopt *
sshauthopt_new_with_keys_defaults(void)
{
	struct sshauthopt *ret = NULL;

	if ((ret = sshauthopt_new()) == NULL)
		return NULL;

	/* Defaults for authorized_keys flags */
	ret->permit_port_forwarding_flag = 1;
	ret->permit_agent_forwarding_flag = 1;
	ret->permit_x11_forwarding_flag = 1;
	ret->permit_pty_flag = 1;
	ret->permit_user_rc = 1;
	return ret;
}