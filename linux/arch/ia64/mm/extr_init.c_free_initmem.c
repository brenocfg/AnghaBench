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
 int /*<<< orphan*/  __init_begin ; 
 int /*<<< orphan*/  __init_end ; 
 int /*<<< orphan*/  free_reserved_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ia64_imva (int /*<<< orphan*/ ) ; 

void
free_initmem (void)
{
	free_reserved_area(ia64_imva(__init_begin), ia64_imva(__init_end),
			   -1, "unused kernel");
}