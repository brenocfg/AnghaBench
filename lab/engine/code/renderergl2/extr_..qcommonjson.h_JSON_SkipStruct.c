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
 int /*<<< orphan*/  IS_STRUCT_CLOSE (char const) ; 
 char* JSON_SkipSeparators (char const*,char const*) ; 
 char* JSON_SkipValueAndSeparators (char const*,char const*) ; 

__attribute__((used)) static const char *JSON_SkipStruct(const char *json, const char *jsonEnd)
{
	json = JSON_SkipSeparators(json + 1, jsonEnd);
	while (json < jsonEnd && !IS_STRUCT_CLOSE(*json))
		json = JSON_SkipValueAndSeparators(json, jsonEnd);

	return (json + 1 > jsonEnd) ? jsonEnd : json + 1;
}