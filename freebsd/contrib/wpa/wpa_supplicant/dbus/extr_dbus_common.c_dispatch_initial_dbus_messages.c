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
typedef  int /*<<< orphan*/  DBusConnection ;

/* Variables and functions */
 int /*<<< orphan*/  dispatch_data (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dispatch_initial_dbus_messages(void *eloop_ctx, void *timeout_ctx)
{
	DBusConnection *con = eloop_ctx;
	dispatch_data(con);
}