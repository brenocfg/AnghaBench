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
struct wpabuf {int dummy; } ;
struct wpa_dbus_argument {scalar_t__ dir; int /*<<< orphan*/  type; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 scalar_t__ ARG_IN ; 
 int /*<<< orphan*/  add_arg (struct wpabuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*,...) ; 

__attribute__((used)) static void add_entry(struct wpabuf *xml, const char *type, const char *name,
		      const struct wpa_dbus_argument *args, int include_dir)
{
	const struct wpa_dbus_argument *arg;

	if (args == NULL || args->name == NULL) {
		wpabuf_printf(xml, "<%s name=\"%s\"/>", type, name);
		return;
	}
	wpabuf_printf(xml, "<%s name=\"%s\">", type, name);
	for (arg = args; arg && arg->name; arg++) {
		add_arg(xml, arg->name, arg->type,
			include_dir ? (arg->dir == ARG_IN ? "in" : "out") :
			NULL);
	}
	wpabuf_printf(xml, "</%s>", type);
}