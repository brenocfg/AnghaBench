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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  next_id; int /*<<< orphan*/  (* callback ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ NotificationCreatedData ;
typedef  int /*<<< orphan*/  DBusMessage ;

/* Variables and functions */
 int /*<<< orphan*/  DBUS_TYPE_INVALID ; 
 int /*<<< orphan*/  DBUS_TYPE_UINT32 ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/  glfw_dbus_get_args (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
notification_created(DBusMessage *msg, const char* errmsg, void *data) {
    if (errmsg) {
        _glfwInputError(GLFW_PLATFORM_ERROR, "Notify: Failed to create notification error: %s", errmsg);
        if (data) free(data);
        return;
    }
    uint32_t notification_id;
    if (!glfw_dbus_get_args(msg, "Failed to get Notification uid", DBUS_TYPE_UINT32, &notification_id, DBUS_TYPE_INVALID)) return;
    NotificationCreatedData *ncd = (NotificationCreatedData*)data;
    if (ncd->callback) ncd->callback(ncd->next_id, notification_id, ncd->data);
    if (data) free(data);
}