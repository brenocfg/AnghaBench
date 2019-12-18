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
struct ipmi_user {int /*<<< orphan*/  intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipmi_poll (int /*<<< orphan*/ ) ; 

void ipmi_poll_interface(struct ipmi_user *user)
{
	ipmi_poll(user->intf);
}