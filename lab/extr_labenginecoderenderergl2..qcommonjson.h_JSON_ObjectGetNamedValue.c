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
 char* JSON_ArrayGetFirstValue (char const*,char const*) ; 
 char* JSON_ArrayGetNextValue (char const*,char const*) ; 
 char* JSON_SkipSeparators (char const*,char const*) ; 
 char* JSON_SkipString (char const*,char const*) ; 
 unsigned int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,unsigned int) ; 

const char *JSON_ObjectGetNamedValue(const char *json, const char *jsonEnd, const char *name)
{
	unsigned int nameLen = strlen(name);

	for (json = JSON_ArrayGetFirstValue(json, jsonEnd); json; json = JSON_ArrayGetNextValue(json, jsonEnd))
	{
		if (*json == '"')
		{
			const char *thisNameStart, *thisNameEnd;

			thisNameStart = json + 1;
			json = JSON_SkipString(json, jsonEnd);
			thisNameEnd = json - 1;
			json = JSON_SkipSeparators(json, jsonEnd);

			if ((unsigned int)(thisNameEnd - thisNameStart) == nameLen)
				if (strncmp(thisNameStart, name, nameLen) == 0)
					return json;
		}
	}

	return NULL;
}