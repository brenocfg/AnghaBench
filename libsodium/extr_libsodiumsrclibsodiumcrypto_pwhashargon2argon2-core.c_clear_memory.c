#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  block ;
struct TYPE_5__ {int memory_blocks; int segment_length; int /*<<< orphan*/ * pseudo_rands; TYPE_1__* region; } ;
typedef  TYPE_2__ argon2_instance_t ;
struct TYPE_4__ {int /*<<< orphan*/ * memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  sodium_memzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
clear_memory(argon2_instance_t *instance, int clear)
{
    /* LCOV_EXCL_START */
    if (clear) {
        if (instance->region != NULL) {
            sodium_memzero(instance->region->memory,
                           sizeof(block) * instance->memory_blocks);
        }
        if (instance->pseudo_rands != NULL) {
            sodium_memzero(instance->pseudo_rands,
                           sizeof(uint64_t) * instance->segment_length);
        }
    }
    /* LCOV_EXCL_STOP */
}