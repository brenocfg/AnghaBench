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
struct subscription {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 char* os_strchr (char const*,char) ; 
 int /*<<< orphan*/  subscr_addr_add_url (struct subscription*,char const*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void subscr_addr_list_create(struct subscription *s,
				    const char *url_list)
{
	const char *end;
	wpa_printf(MSG_DEBUG, "WPS UPnP: Parsing URL list '%s'", url_list);
	for (;;) {
		while (*url_list == ' ' || *url_list == '\t')
			url_list++;
		if (*url_list != '<')
			break;
		url_list++;
		end = os_strchr(url_list, '>');
		if (end == NULL)
			break;
		subscr_addr_add_url(s, url_list, end - url_list);
		url_list = end + 1;
	}
}