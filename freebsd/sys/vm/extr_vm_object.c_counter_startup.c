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
 int /*<<< orphan*/  M_WAITOK ; 
 void* counter_u64_alloc (int /*<<< orphan*/ ) ; 
 void* object_bypasses ; 
 void* object_collapses ; 

__attribute__((used)) static void
counter_startup(void)
{

	object_collapses = counter_u64_alloc(M_WAITOK);
	object_bypasses = counter_u64_alloc(M_WAITOK);
}