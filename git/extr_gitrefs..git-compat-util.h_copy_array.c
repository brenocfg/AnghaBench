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
 int /*<<< orphan*/  memcpy (void*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_mult (size_t,size_t) ; 

__attribute__((used)) static inline void copy_array(void *dst, const void *src, size_t n, size_t size)
{
	if (n)
		memcpy(dst, src, st_mult(size, n));
}