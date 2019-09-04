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
typedef  int /*<<< orphan*/  DBusMessageIter ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 scalar_t__ DBUS_TYPE_STRING ; 
 scalar_t__ DBUS_TYPE_STRUCT ; 
 scalar_t__ DBUS_TYPE_VARIANT ; 
 scalar_t__ dbus_message_iter_get_arg_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_get_basic (int /*<<< orphan*/ *,char const**) ; 
 int /*<<< orphan*/  dbus_message_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbus_message_iter_recurse (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static const char*
get_ibus_text_from_message(DBusMessage *msg) {
    /* The message structure is (from dbus-monitor)
       variant       struct {
         string "IBusText"
         array [
         ]
         string "ash "
         variant             struct {
               string "IBusAttrList"
               array [
               ]
               array [
               ]
            }
      }
    */
    const char *text = NULL;
    const char *struct_id = NULL;
    DBusMessageIter iter, sub1, sub2;
    dbus_message_iter_init(msg, &iter);

    if (dbus_message_iter_get_arg_type(&iter) != DBUS_TYPE_VARIANT) return NULL;

    dbus_message_iter_recurse(&iter, &sub1);

    if (dbus_message_iter_get_arg_type(&sub1) != DBUS_TYPE_STRUCT) return NULL;

    dbus_message_iter_recurse(&sub1, &sub2);

    if (dbus_message_iter_get_arg_type(&sub2) != DBUS_TYPE_STRING) return NULL;

    dbus_message_iter_get_basic(&sub2, &struct_id);
    if (!struct_id || strncmp(struct_id, "IBusText", sizeof("IBusText")) != 0) return NULL;

    dbus_message_iter_next(&sub2);
    dbus_message_iter_next(&sub2);

    if (dbus_message_iter_get_arg_type(&sub2) != DBUS_TYPE_STRING) return NULL;

    dbus_message_iter_get_basic(&sub2, &text);

    return text;
}