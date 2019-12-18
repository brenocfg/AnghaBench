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
 scalar_t__ isascii (int) ; 
 scalar_t__ isupper (int) ; 
 char* malloc (scalar_t__) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  tolower (int) ; 

__attribute__((used)) static char *unify(const char *src)
{
	const char *sptr;
	char *dst, *dptr;
	int c;

	if (!(dst = malloc(strlen(src) + 1)))
		return NULL;

	sptr = src;
	dptr = dst;
	do {
		c = (unsigned char)*sptr;
		if (isascii(c) && isupper(c))
			*dptr++ = tolower(c);
		else
			*dptr++ = *sptr;
	} while (*sptr++);

	return dst;
}