#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ga_Bytes; } ;
typedef  TYPE_1__ Guard ;

/* Variables and functions */
 int DidAtExit ; 
 int /*<<< orphan*/  Free (void*,char const*,int) ; 
 int MALLOCALIGN ; 
 void* Malloc (size_t,char const*,int) ; 
 scalar_t__ MallocCount ; 
 scalar_t__ MallocMax ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (void*,void*,size_t) ; 
 int /*<<< orphan*/  mallocstats ; 

void *
Realloc(void *ptr, size_t size, const char *file, int line)
{
	void *res;
	size_t old;

	if ((res = Malloc(size, file, line)) != NULL) {
		if (ptr != NULL) {
			Guard *g = (Guard *)((char *)ptr - MALLOCALIGN);

			old = g->ga_Bytes - MALLOCALIGN;
			if (old < size)
				bcopy(ptr, res, old);
			else
				bcopy(ptr, res, size);
			Free(ptr, file, line);
		} else {
#ifdef DMALLOCDEBUG
			if (++MallocCount > MallocMax)
				MallocMax = MallocCount;
#ifdef EXITSTATS
			if (DidAtExit == 0) {
				DidAtExit = 1;
				atexit(mallocstats);
			}
#endif
#endif
		}
	}
	return (res);
}