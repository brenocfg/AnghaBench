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
 void* calloc (size_t,size_t) ; 
 scalar_t__ flushentry () ; 

__attribute__((used)) static inline void*
Calloc(size_t cnt, size_t size)
{
	void *retval;

	while ((retval = calloc(cnt, size)) == NULL)
		if (flushentry() == 0)
			break;
	return (retval);
}