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
 unsigned long DEFAULT_MAP_WINDOW ; 
 unsigned long TASK_SIZE_MAX ; 

unsigned long task_size_64bit(int full_addr_space)
{
	return full_addr_space ? TASK_SIZE_MAX : DEFAULT_MAP_WINDOW;
}