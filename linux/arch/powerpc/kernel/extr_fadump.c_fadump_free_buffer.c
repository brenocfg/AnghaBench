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
 int /*<<< orphan*/  free_reserved_area (void*,void*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fadump_free_buffer(unsigned long vaddr, unsigned long size)
{
	free_reserved_area((void *)vaddr, (void *)(vaddr + size), -1, NULL);
}