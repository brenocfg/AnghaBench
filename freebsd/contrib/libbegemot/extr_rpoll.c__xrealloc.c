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
 int /*<<< orphan*/  _panic (char*,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 void* realloc (void*,size_t) ; 

__attribute__((used)) static void *
_xrealloc(void *p, size_t s)
{
	void *ptr;

	if(p == NULL) {
		if((ptr=malloc(s)) == NULL && (s!=0 || (ptr=malloc(1)) == NULL))
			_panic("out of memory: xrealloc(%lx, %lu)",
				(unsigned long)p, (unsigned long)s);
	} else if(s == 0) {
		free(p);
		if((ptr=malloc(s)) == NULL && (ptr=malloc(1)) == NULL)
			_panic("out of memory: xrealloc(%lx, %lu)",
				(unsigned long)p, (unsigned long)s);
	} else {
		if((ptr = realloc(p, s)) == NULL)
			_panic("out of memory: xrealloc(%lx, %lu)",
				(unsigned long)p, (unsigned long)s);
	}

	return ptr;
}