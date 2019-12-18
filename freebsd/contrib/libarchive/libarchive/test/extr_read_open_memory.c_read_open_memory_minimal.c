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
struct archive {int dummy; } ;

/* Variables and functions */
 int read_open_memory_internal (struct archive*,void const*,size_t,size_t,int) ; 

int
read_open_memory_minimal(struct archive *a, const void *buff, size_t size, size_t read_size)
{
	return read_open_memory_internal(a, buff, size, read_size, 1);
}