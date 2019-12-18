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
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (void*,char const*,size_t) ; 

void
strncpy_cond(void *dst, const char *src, bool cond) {
	if (cond) {
		/*
		 * Avoid strcpy and explicitly set length to 0 because the
		 * `stringop-overflow` check may warn even if the specific test
		 * is unreachable.
		 */
		size_t n = cond ? strlen(src) + 1 : 0;
		strncpy(dst, src, n);
	}
}