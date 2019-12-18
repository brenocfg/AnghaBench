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
 int /*<<< orphan*/  isgraph (char const) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,int) ; 
 int os_strlen (char const*) ; 
 int /*<<< orphan*/  os_strncasecmp (char const*,char const*,int) ; 
 char* os_zalloc (int) ; 
 scalar_t__ xml_next_tag (char const*,char const**,char const**,char const**) ; 

char * xml_get_first_item(const char *doc, const char *item)
{
	const char *match = item;
	int match_len = os_strlen(item);
	const char *tag, *tagname, *end;
	char *value;

	/*
	 * This is crude: ignore any possible tag name conflicts and go right
	 * to the first tag of this name. This should be ok for the limited
	 * domain of UPnP messages.
	 */
	for (;;) {
		if (xml_next_tag(doc, &tag, &tagname, &end))
			return NULL;
		doc = end;
		if (!os_strncasecmp(tagname, match, match_len) &&
		    *tag != '/' &&
		    (tagname[match_len] == '>' ||
		     !isgraph(tagname[match_len]))) {
			break;
		}
	}
	end = doc;
	while (*end && *end != '<')
		end++;
	value = os_zalloc(1 + (end - doc));
	if (value == NULL)
		return NULL;
	os_memcpy(value, doc, end - doc);
	return value;
}