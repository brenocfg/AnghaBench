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
 unsigned long FIRST_FEW_BYTES ; 
 int /*<<< orphan*/  memchr (char const*,int /*<<< orphan*/ ,unsigned long) ; 

int buffer_is_binary(const char *ptr, unsigned long size)
{
	if (FIRST_FEW_BYTES < size)
		size = FIRST_FEW_BYTES;
	return !!memchr(ptr, 0, size);
}