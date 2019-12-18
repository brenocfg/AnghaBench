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
 int /*<<< orphan*/  CTL_P1003_1B_FSYNC ; 
 int /*<<< orphan*/  CTL_P1003_1B_MAPPED_FILES ; 
 int /*<<< orphan*/  CTL_P1003_1B_PAGESIZE ; 
 int /*<<< orphan*/  CTL_P1003_1B_SHARED_MEMORY_OBJECTS ; 
 long PAGE_SIZE ; 
 int /*<<< orphan*/  p31b_setcfg (int /*<<< orphan*/ ,long) ; 

__attribute__((used)) static void
p31b_set_standard(void *dummy)
{

	p31b_setcfg(CTL_P1003_1B_FSYNC, 200112L);
	p31b_setcfg(CTL_P1003_1B_MAPPED_FILES, 200112L);
	p31b_setcfg(CTL_P1003_1B_SHARED_MEMORY_OBJECTS, 200112L);
	p31b_setcfg(CTL_P1003_1B_PAGESIZE, PAGE_SIZE);
}