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
 int /*<<< orphan*/  bcopy (char const*,char*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 char* malloc (unsigned int) ; 
 int strlen (char const*) ; 

char *
vcopy(const char *str)
{
	char *new;
	unsigned len;

	if (*str == '\0')
		return ("");
	len = strlen(str) + 1;
	if ((new = malloc(len)) == NULL)
		err(1, "Out of memory");
	bcopy(str, new, (int)len);
	return (new);
}