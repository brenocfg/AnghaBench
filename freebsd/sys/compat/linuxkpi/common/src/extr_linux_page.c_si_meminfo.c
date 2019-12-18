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
struct sysinfo {int /*<<< orphan*/  mem_unit; scalar_t__ totalhigh; int /*<<< orphan*/  totalram; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  physmem ; 

void
si_meminfo(struct sysinfo *si)
{
	si->totalram = physmem;
	si->totalhigh = 0;
	si->mem_unit = PAGE_SIZE;
}