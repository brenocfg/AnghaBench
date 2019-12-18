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
struct heim_base_mem {int /*<<< orphan*/  (* dealloc ) (void*) ;} ;

/* Variables and functions */
 scalar_t__ PTR2BASE (void*) ; 
 int /*<<< orphan*/  stub1 (void*) ; 

__attribute__((used)) static void
memory_dealloc(void *ptr)
{
    struct heim_base_mem *p = (struct heim_base_mem *)PTR2BASE(ptr);
    if (p->dealloc)
	p->dealloc(ptr);
}