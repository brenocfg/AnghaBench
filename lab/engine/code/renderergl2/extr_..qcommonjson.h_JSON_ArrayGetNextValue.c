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
 scalar_t__ IS_STRUCT_CLOSE (char const) ; 
 char* JSON_SkipValueAndSeparators (char const*,char const*) ; 

const char *JSON_ArrayGetNextValue(const char *json, const char *jsonEnd)
{
	if (!json || json >= jsonEnd || IS_STRUCT_CLOSE(*json))
		return NULL;

	json = JSON_SkipValueAndSeparators(json, jsonEnd);

	return (json >= jsonEnd || IS_STRUCT_CLOSE(*json)) ? NULL : json;
}