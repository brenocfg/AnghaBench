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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  GLFWDBusnotificationcreatedfun ;

/* Variables and functions */
 unsigned long long glfw_dbus_send_user_notification (char const*,char const*,char const*,char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

unsigned long long glfwDBusUserNotify(const char *app_name, const char* icon, const char *summary, const char *body, const char *action_name, int32_t timeout, GLFWDBusnotificationcreatedfun callback, void *data) {
    return glfw_dbus_send_user_notification(app_name, icon, summary, body, action_name, timeout, callback, data);
}