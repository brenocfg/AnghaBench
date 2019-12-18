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
 void* heim_alloc (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heim_release (void*) ; 
 int /*<<< orphan*/  heim_retain (void*) ; 
 int /*<<< orphan*/ * memory_free ; 

__attribute__((used)) static int
test_memory(void)
{
    void *ptr;

    ptr = heim_alloc(10, "memory", memory_free);

    heim_retain(ptr);
    heim_release(ptr);

    heim_retain(ptr);
    heim_release(ptr);

    heim_release(ptr);

    ptr = heim_alloc(10, "memory", NULL);
    heim_release(ptr);

    return 0;
}