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
 scalar_t__ isspace (char const) ; 
 int strcspn (char const*,char*) ; 
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static const char *parse_feature_value(const char *feature_list, const char *feature, int *lenp)
{
	int len;

	if (!feature_list)
		return NULL;

	len = strlen(feature);
	while (*feature_list) {
		const char *found = strstr(feature_list, feature);
		if (!found)
			return NULL;
		if (feature_list == found || isspace(found[-1])) {
			const char *value = found + len;
			/* feature with no value (e.g., "thin-pack") */
			if (!*value || isspace(*value)) {
				if (lenp)
					*lenp = 0;
				return value;
			}
			/* feature with a value (e.g., "agent=git/1.2.3") */
			else if (*value == '=') {
				value++;
				if (lenp)
					*lenp = strcspn(value, " \t\n");
				return value;
			}
			/*
			 * otherwise we matched a substring of another feature;
			 * keep looking
			 */
		}
		feature_list = found + 1;
	}
	return NULL;
}