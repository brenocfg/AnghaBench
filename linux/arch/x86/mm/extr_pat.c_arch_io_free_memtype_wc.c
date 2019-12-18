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
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  io_free_memtype (scalar_t__,scalar_t__) ; 

void arch_io_free_memtype_wc(resource_size_t start, resource_size_t size)
{
	io_free_memtype(start, start + size);
}