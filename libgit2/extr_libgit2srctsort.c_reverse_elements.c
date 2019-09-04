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
typedef  size_t ssize_t ;

/* Variables and functions */

__attribute__((used)) static void reverse_elements(void **dst, ssize_t start, ssize_t end)
{
	while (start < end) {
		void *tmp = dst[start];
		dst[start] = dst[end];
		dst[end] = tmp;

		start++;
		end--;
	}
}