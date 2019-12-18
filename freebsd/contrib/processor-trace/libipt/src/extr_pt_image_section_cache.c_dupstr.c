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
 char* malloc (size_t) ; 
 char* memcpy (char*,char const*,size_t) ; 
 size_t strnlen (char const*,unsigned long) ; 

__attribute__((used)) static char *dupstr(const char *str)
{
	char *dup;
	size_t len;

	if (!str)
		return NULL;

	/* Silently truncate the name if it gets too big. */
	len = strnlen(str, 4096ul);

	dup = malloc(len + 1);
	if (!dup)
		return NULL;

	dup[len] = 0;

	return memcpy(dup, str, len);
}