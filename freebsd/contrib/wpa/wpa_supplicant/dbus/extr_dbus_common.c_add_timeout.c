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
struct wpas_dbus_priv {int dummy; } ;
typedef  int /*<<< orphan*/  dbus_bool_t ;
typedef  int /*<<< orphan*/  DBusTimeout ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  dbus_timeout_get_enabled (int /*<<< orphan*/ *) ; 
 int dbus_timeout_get_interval (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_timeout_set_data (int /*<<< orphan*/ *,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_timeout ; 

__attribute__((used)) static dbus_bool_t add_timeout(DBusTimeout *timeout, void *data)
{
	struct wpas_dbus_priv *priv = data;

	if (!dbus_timeout_get_enabled(timeout))
		return TRUE;

	eloop_register_timeout(0, dbus_timeout_get_interval(timeout) * 1000,
			       process_timeout, priv, timeout);

	dbus_timeout_set_data(timeout, priv, NULL);

	return TRUE;
}