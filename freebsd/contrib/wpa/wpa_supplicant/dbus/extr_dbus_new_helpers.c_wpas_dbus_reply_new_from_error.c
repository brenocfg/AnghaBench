#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* name; char const* message; } ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  TYPE_1__ DBusError ;

/* Variables and functions */
 int /*<<< orphan*/ * dbus_message_new_error (int /*<<< orphan*/ *,char const*,char const*) ; 

DBusMessage * wpas_dbus_reply_new_from_error(DBusMessage *message,
					     DBusError *error,
					     const char *fallback_name,
					     const char *fallback_string)
{
	if (error && error->name && error->message) {
		return dbus_message_new_error(message, error->name,
					      error->message);
	}
	if (fallback_name && fallback_string) {
		return dbus_message_new_error(message, fallback_name,
					      fallback_string);
	}
	return NULL;
}