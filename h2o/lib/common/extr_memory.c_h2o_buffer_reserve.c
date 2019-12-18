#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * base; } ;
typedef  TYPE_1__ h2o_iovec_t ;
struct TYPE_8__ {int /*<<< orphan*/  capacity; } ;
typedef  TYPE_2__ h2o_buffer_t ;

/* Variables and functions */
 TYPE_1__ h2o_buffer_try_reserve (TYPE_2__**,size_t) ; 
 int /*<<< orphan*/  h2o_fatal (char*,int /*<<< orphan*/ ,size_t) ; 

h2o_iovec_t h2o_buffer_reserve(h2o_buffer_t **_inbuf, size_t min_guarantee)
{
    h2o_iovec_t reserved = h2o_buffer_try_reserve(_inbuf, min_guarantee);
    if (reserved.base == NULL) {
        h2o_fatal("failed to reserve buffer; capacity: %zu, min_gurantee: %zu", (*_inbuf)->capacity, min_guarantee);
    }
    return reserved;
}