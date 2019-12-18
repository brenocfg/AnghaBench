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
 char* do_malloc (unsigned int) ; 

__attribute__((used)) static char *
copy(const char *str, unsigned int len)
{
	char *new, *sp;

	new = do_malloc(len + 1);
	sp = new;
	do {
		*sp++ = *str;
	} while (*str++);

	return (new);
}