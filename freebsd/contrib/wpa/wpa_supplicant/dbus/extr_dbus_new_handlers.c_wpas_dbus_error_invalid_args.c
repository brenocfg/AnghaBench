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
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_STRING ; 
 int /*<<< orphan*/  WPAS_DBUS_ERROR_INVALID_ARGS ; 
 int /*<<< orphan*/  dbus_message_append_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

DBusMessage * wpas_dbus_error_invalid_args(DBusMessage *message,
					  const char *arg)
{
	DBusMessage *reply;

	reply = dbus_message_new_error(
		message, WPAS_DBUS_ERROR_INVALID_ARGS,
		"Did not receive correct message arguments.");
	if (arg != NULL)
		dbus_message_append_args(reply, DBUS_TYPE_STRING, &arg,
					 DBUS_TYPE_INVALID);

	return reply;
}