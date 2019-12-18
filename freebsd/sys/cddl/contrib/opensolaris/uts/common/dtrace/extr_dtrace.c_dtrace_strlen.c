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
typedef  size_t uint_t ;

/* Variables and functions */
 char dtrace_load8 (uintptr_t) ; 

__attribute__((used)) static size_t
dtrace_strlen(const char *s, size_t lim)
{
	uint_t len;

	for (len = 0; len != lim; len++) {
		if (dtrace_load8((uintptr_t)s++) == '\0')
			break;
	}

	return (len);
}