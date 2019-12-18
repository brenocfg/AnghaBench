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
 int /*<<< orphan*/  blacklist_r (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * blstate ; 
 scalar_t__ packet_connection_is_on_socket () ; 
 int /*<<< orphan*/  packet_get_connection_in () ; 

void
blacklist_notify(int action, const char *msg)
{

	if (blstate != NULL && packet_connection_is_on_socket())
		(void)blacklist_r(blstate, action,
		packet_get_connection_in(), msg);
}