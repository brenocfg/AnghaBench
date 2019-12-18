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
 int /*<<< orphan*/  IS_STRUCT_OPEN (char const) ; 
 char* JSON_SkipSeparators (char const*,char const*) ; 

const char *JSON_ArrayGetFirstValue(const char *json, const char *jsonEnd)
{
	if (!json || json >= jsonEnd || !IS_STRUCT_OPEN(*json))
		return NULL;

	json = JSON_SkipSeparators(json + 1, jsonEnd);

	return (json >= jsonEnd || IS_STRUCT_CLOSE(*json)) ? NULL : json;
}