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
 int /*<<< orphan*/  free (void*) ; 
 void* tfff_p1 ; 
 int /*<<< orphan*/  tfff_p1_freed ; 
 void* tfff_p2 ; 
 int /*<<< orphan*/  tfff_p2_freed ; 

__attribute__((used)) static void
tfff_free(void *p)
{
	if (! p)
		return;
	if (p == tfff_p1)
		++tfff_p1_freed;
	if (p == tfff_p2)
		++tfff_p2_freed;
	free(p);
}