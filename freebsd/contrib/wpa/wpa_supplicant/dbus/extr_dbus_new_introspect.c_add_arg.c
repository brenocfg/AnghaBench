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

/* Variables and functions */
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*) ; 
 int /*<<< orphan*/  wpabuf_put_str (struct wpabuf*,char*) ; 

__attribute__((used)) static void add_arg(struct wpabuf *xml, const char *name, const char *type,
		    const char *direction)
{
	wpabuf_printf(xml, "<arg name=\"%s\"", name);
	if (type)
		wpabuf_printf(xml, " type=\"%s\"", type);
	if (direction)
		wpabuf_printf(xml, " direction=\"%s\"", direction);
	wpabuf_put_str(xml, "/>");
}