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
typedef  int /*<<< orphan*/  DBusTimeout ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_timeout_handle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void process_timeout(void *eloop_ctx, void *sock_ctx)
{
	DBusTimeout *timeout = sock_ctx;
	dbus_timeout_handle(timeout);
}