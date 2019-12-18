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
 char* JSON_SkipValue (char const*,char const*) ; 

unsigned int JSON_ValueGetString(const char *json, const char *jsonEnd, char *outString, unsigned int stringLen)
{
	const char *stringEnd, *stringStart;

	if (!json)
	{
		*outString = '\0';
		return 0;
	}

	stringStart = json;
	stringEnd = JSON_SkipValue(stringStart, jsonEnd);
	if (stringEnd >= jsonEnd)
	{
		*outString = '\0';
		return 0;
	}

	// skip enclosing quotes if they exist
	if (*stringStart == '"')
		stringStart++;

	if (*(stringEnd - 1) == '"')
		stringEnd--;

	stringLen--;
	if (stringLen > stringEnd - stringStart)
		stringLen = stringEnd - stringStart;

	json = stringStart;
	while (stringLen--)
		*outString++ = *json++;
	*outString = '\0';

	return stringEnd - stringStart;
}