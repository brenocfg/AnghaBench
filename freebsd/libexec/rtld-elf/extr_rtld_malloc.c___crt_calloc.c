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
 void* __crt_malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *
__crt_calloc(size_t num, size_t size)
{
	void *ret;

	if (size != 0 && (num * size) / size != num) {
		/* size_t overflow. */
		return (NULL);
	}

	if ((ret = __crt_malloc(num * size)) != NULL)
		memset(ret, 0, num * size);

	return (ret);
}