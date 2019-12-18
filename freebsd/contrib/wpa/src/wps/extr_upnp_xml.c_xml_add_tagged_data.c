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
 int /*<<< orphan*/  os_strlen (char const*) ; 
 int /*<<< orphan*/  wpabuf_printf (struct wpabuf*,char*,char const*) ; 
 int /*<<< orphan*/  xml_data_encode (struct wpabuf*,char const*,int /*<<< orphan*/ ) ; 

void xml_add_tagged_data(struct wpabuf *buf, const char *tag, const char *data)
{
	wpabuf_printf(buf, "<%s>", tag);
	xml_data_encode(buf, data, os_strlen(data));
	wpabuf_printf(buf, "</%s>\n", tag);
}