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
 int /*<<< orphan*/  add_timeout (int /*<<< orphan*/ *,void*) ; 
 scalar_t__ dbus_timeout_get_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_timeout (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static void timeout_toggled(DBusTimeout *timeout, void *data)
{
	if (dbus_timeout_get_enabled(timeout))
		add_timeout(timeout, data);
	else
		remove_timeout(timeout, data);
}