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
 int strcmp (char const*,char const*) ; 

__attribute__((used)) static int
compare_lang(const void *a, const void *b)
{
	const char *l1 = *((const char * const *) a);
	const char *l2 = *((const char * const *) b);

	return strcmp(l1, l2);
}