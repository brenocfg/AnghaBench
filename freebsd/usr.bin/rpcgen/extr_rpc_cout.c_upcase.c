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
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  toupper (int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (scalar_t__) ; 

char *
upcase(const char *str)
{
	char *ptr, *hptr;

	ptr = (char *)xmalloc(strlen(str)+1);

	hptr = ptr;
	while (*str != '\0')
		*ptr++ = toupper(*str++);

	*ptr = '\0';
	return (hptr);
}