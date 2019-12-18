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
 void* ____memcpy (void*,void const*,size_t) ; 
 void* memmove (void*,void const*,size_t) ; 
 int /*<<< orphan*/  warn (char*) ; 

void *memcpy(void *dest, const void *src, size_t n)
{
	if (dest > src && dest - src < n) {
		warn("Avoiding potentially unsafe overlapping memcpy()!");
		return memmove(dest, src, n);
	}
	return ____memcpy(dest, src, n);
}