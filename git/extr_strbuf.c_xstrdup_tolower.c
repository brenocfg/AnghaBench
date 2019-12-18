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
 size_t strlen (char const*) ; 
 char tolower (char const) ; 
 char* xmallocz (size_t) ; 

char *xstrdup_tolower(const char *string)
{
	char *result;
	size_t len, i;

	len = strlen(string);
	result = xmallocz(len);
	for (i = 0; i < len; i++)
		result[i] = tolower(string[i]);
	return result;
}