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
 void* Malloc (uintptr_t,char const*,int) ; 
 scalar_t__ MallocCount ; 
 scalar_t__ MallocMax ; 
 int /*<<< orphan*/  bzero (void*,uintptr_t) ; 

void *
Calloc(size_t n1, size_t n2, const char *file, int line)
{
	uintptr_t bytes = (uintptr_t)n1 * (uintptr_t)n2;
	void *res;

	if ((res = Malloc(bytes, file, line)) != NULL) {
		bzero(res, bytes);
#ifdef DMALLOCDEBUG
		if (++MallocCount > MallocMax)
			MallocMax = MallocCount;
#endif
	}
	return (res);
}