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

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  isgraph (char const) ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  os_strncasecmp (char const*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,char*) ; 
 char* xml_get_first_item (char const*,char*) ; 
 scalar_t__ xml_next_tag (char const*,char const**,char const**,char const**) ; 

__attribute__((used)) static const char * wps_er_find_wfadevice(const char *data)
{
	const char *tag, *tagname, *end;
	char *val;
	int found = 0;

	while (!found) {
		/* Find next <device> */
		for (;;) {
			if (xml_next_tag(data, &tag, &tagname, &end))
				return NULL;
			data = end;
			if (!os_strncasecmp(tagname, "device", 6) &&
			    *tag != '/' &&
			    (tagname[6] == '>' || !isgraph(tagname[6]))) {
				break;
			}
		}

		/* Check whether deviceType is WFADevice */
		val = xml_get_first_item(data, "deviceType");
		if (val == NULL)
			return NULL;
		wpa_printf(MSG_DEBUG, "WPS ER: Found deviceType '%s'", val);
		found = os_strcasecmp(val, "urn:schemas-wifialliance-org:"
				      "device:WFADevice:1") == 0;
		os_free(val);
	}

	return data;
}