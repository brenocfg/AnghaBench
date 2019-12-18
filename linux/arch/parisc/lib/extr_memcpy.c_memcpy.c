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
 int /*<<< orphan*/  get_kernel_space () ; 
 int /*<<< orphan*/  mtsp (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pa_memcpy (void*,void const*,size_t) ; 

void * memcpy(void * dst,const void *src, size_t count)
{
	mtsp(get_kernel_space(), 1);
	mtsp(get_kernel_space(), 2);
	pa_memcpy(dst, src, count);
	return dst;
}