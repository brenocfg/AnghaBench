#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * region; int /*<<< orphan*/ * pseudo_rands; } ;
typedef  TYPE_1__ argon2_instance_t ;

/* Variables and functions */
 int ARGON2_FLAG_CLEAR_MEMORY ; 
 int /*<<< orphan*/  clear_memory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_memory (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
argon2_free_instance(argon2_instance_t *instance, int flags)
{
    /* Clear memory */
    clear_memory(instance, flags & ARGON2_FLAG_CLEAR_MEMORY);

    /* Deallocate the memory */
    free(instance->pseudo_rands);
    instance->pseudo_rands = NULL;
    free_memory(instance->region);
    instance->region = NULL;
}