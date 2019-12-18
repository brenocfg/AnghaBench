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
 char* malloc (int) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static char *reverse(const char *src)
{
	const char *sptr;
	char *dst, *dptr;

	if (!(dst = malloc(strlen(src) + 1)))
		return NULL;

	sptr = &src[strlen(src)];
	dptr = dst;
	while (sptr > src)
		*dptr++ = *--sptr;
	*dptr = '\0';

	return dst;
}