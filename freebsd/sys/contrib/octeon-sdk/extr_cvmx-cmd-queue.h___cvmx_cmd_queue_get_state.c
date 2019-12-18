#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int cvmx_cmd_queue_id_t ;
typedef  int /*<<< orphan*/  __cvmx_cmd_queue_state_t ;
struct TYPE_2__ {int /*<<< orphan*/ * state; } ;

/* Variables and functions */
 int CVMX_CMD_QUEUE_END ; 
 scalar_t__ CVMX_ENABLE_PARAMETER_CHECKING ; 
 size_t __cvmx_cmd_queue_get_index (int) ; 
 TYPE_1__* __cvmx_cmd_queue_state_ptr ; 
 scalar_t__ cvmx_unlikely (int) ; 

__attribute__((used)) static inline __cvmx_cmd_queue_state_t *__cvmx_cmd_queue_get_state(cvmx_cmd_queue_id_t queue_id)
{
    if (CVMX_ENABLE_PARAMETER_CHECKING)
    {
        if (cvmx_unlikely(queue_id >= CVMX_CMD_QUEUE_END))
            return NULL;
        if (cvmx_unlikely((queue_id & 0xffff) >= 256))
            return NULL;
    }
    return &__cvmx_cmd_queue_state_ptr->state[__cvmx_cmd_queue_get_index(queue_id)];
}