#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_id_t ;
struct TYPE_3__ {scalar_t__ base_ptr_div128; } ;
typedef  TYPE_1__ __cvmx_cmd_queue_state_t ;

/* Variables and functions */
 TYPE_1__* __cvmx_cmd_queue_get_state (int /*<<< orphan*/ ) ; 
 void* cvmx_phys_to_ptr (int) ; 

void *cvmx_cmd_queue_buffer(cvmx_cmd_queue_id_t queue_id)
{
    __cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);
    if (qptr && qptr->base_ptr_div128)
        return cvmx_phys_to_ptr((uint64_t)qptr->base_ptr_div128<<7);
    else
        return NULL;
}