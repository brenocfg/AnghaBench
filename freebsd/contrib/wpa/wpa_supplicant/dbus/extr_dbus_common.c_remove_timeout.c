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
typedef  int /*<<< orphan*/  DBusTimeout ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_timeout_set_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpas_dbus_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_timeout ; 

__attribute__((used)) static void remove_timeout(DBusTimeout *timeout, void *data)
{
	struct wpas_dbus_priv *priv = data;

	eloop_cancel_timeout(process_timeout, priv, timeout);
	dbus_timeout_set_data(timeout, NULL, NULL);
}