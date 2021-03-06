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
 int /*<<< orphan*/  os_memmove (unsigned char*,unsigned char*,size_t) ; 

__attribute__((used)) static inline void os_remove_in_array(void *ptr, size_t nmemb, size_t size,
				      size_t idx)
{
	if (idx < nmemb - 1)
		os_memmove(((unsigned char *) ptr) + idx * size,
			   ((unsigned char *) ptr) + (idx + 1) * size,
			   (nmemb - idx - 1) * size);
}