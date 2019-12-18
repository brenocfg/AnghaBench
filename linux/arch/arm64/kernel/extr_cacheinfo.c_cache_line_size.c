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
 int cache_line_size_of_cpu () ; 
 scalar_t__ coherency_max_size ; 

int cache_line_size(void)
{
	if (coherency_max_size != 0)
		return coherency_max_size;

	return cache_line_size_of_cpu();
}