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
 scalar_t__ MANDOCLEVEL_SYSERR ; 
 int /*<<< orphan*/  err (int,int /*<<< orphan*/ *) ; 
 char* strndup (char const*,size_t) ; 

char *
mandoc_strndup(const char *ptr, size_t sz)
{
	char	*p;

	p = strndup(ptr, sz);
	if (p == NULL)
		err((int)MANDOCLEVEL_SYSERR, NULL);
	return p;
}