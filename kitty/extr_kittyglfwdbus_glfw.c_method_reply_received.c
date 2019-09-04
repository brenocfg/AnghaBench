#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ MethodResponse ;
typedef  int /*<<< orphan*/  DBusPendingCall ;
typedef  int /*<<< orphan*/  DBusMessage ;
typedef  int /*<<< orphan*/  DBusError ;

/* Variables and functions */
 int /*<<< orphan*/  dbus_error_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dbus_pending_call_steal_reply (int /*<<< orphan*/ *) ; 
 scalar_t__ dbus_set_error_from_message (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * format_message_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
method_reply_received(DBusPendingCall *pending, void *user_data) {
    MethodResponse *res = (MethodResponse*)user_data;
    DBusMessage *msg = dbus_pending_call_steal_reply(pending);
    if (msg) {
        DBusError err;
        dbus_error_init(&err);
        if (dbus_set_error_from_message(&err, msg)) res->callback(NULL, format_message_error(&err), res->user_data);
        else res->callback(msg, NULL, res->user_data);
        dbus_message_unref(msg);
    }
}