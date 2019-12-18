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
 char* os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,char const*,size_t) ; 
 size_t os_strlen (char const*) ; 

char * os_strdup(const char *s)
{
	char *res;
	size_t len;
	if (s == NULL)
		return NULL;
	len = os_strlen(s);
	res = os_malloc(len + 1);
	if (res)
		os_memcpy(res, s, len + 1);
	return res;
}