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
 void* stdalloc__reallocarray (int /*<<< orphan*/ *,size_t,size_t,char const*,int) ; 

__attribute__((used)) static void *stdalloc__mallocarray(size_t nelem, size_t elsize, const char *file, int line)
{
	return stdalloc__reallocarray(NULL, nelem, elsize, file, line);
}