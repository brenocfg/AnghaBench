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
 int strlen (char const*) ; 

char *
strdup(const char *str)
{
	size_t len;
	char *cp;

	len = strlen(str) + 1;
	cp = malloc(len);
	if (cp != NULL)
		return(memcpy(cp, str, len));
	return NULL;
}