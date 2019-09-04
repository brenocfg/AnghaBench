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
 scalar_t__ GIT_ADD_SIZET_OVERFLOW (size_t*,size_t,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* stdalloc__malloc (size_t,char const*,int) ; 

__attribute__((used)) static char *stdalloc__substrdup(const char *start, size_t n, const char *file, int line)
{
	char *ptr;
	size_t alloclen;

	if (GIT_ADD_SIZET_OVERFLOW(&alloclen, n, 1) ||
		!(ptr = stdalloc__malloc(alloclen, file, line)))
		return NULL;

	memcpy(ptr, start, n);
	ptr[n] = '\0';
	return ptr;
}