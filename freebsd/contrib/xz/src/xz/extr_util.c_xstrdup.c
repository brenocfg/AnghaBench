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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char* memcpy (char*,char const*,size_t const) ; 
 int strlen (char const*) ; 
 char* xmalloc (size_t const) ; 

extern char *
xstrdup(const char *src)
{
	assert(src != NULL);
	const size_t size = strlen(src) + 1;
	char *dest = xmalloc(size);
	return memcpy(dest, src, size);
}