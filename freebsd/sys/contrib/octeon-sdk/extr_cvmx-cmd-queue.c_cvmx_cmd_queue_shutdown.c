#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_result_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_id_t ;
struct TYPE_5__ {scalar_t__ base_ptr_div128; int /*<<< orphan*/  fpa_pool; } ;
typedef  TYPE_1__ __cvmx_cmd_queue_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_CMD_QUEUE_FULL ; 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_INVALID_PARAM ; 
 int /*<<< orphan*/  CVMX_CMD_QUEUE_SUCCESS ; 
 TYPE_1__* __cvmx_cmd_queue_get_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_cmd_queue_lock (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  __cvmx_cmd_queue_unlock (TYPE_1__*) ; 
 scalar_t__ cvmx_cmd_queue_length (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*) ; 
 int /*<<< orphan*/  cvmx_fpa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_phys_to_ptr (int) ; 

cvmx_cmd_queue_result_t cvmx_cmd_queue_shutdown(cvmx_cmd_queue_id_t queue_id)
{
    __cvmx_cmd_queue_state_t *qptr = __cvmx_cmd_queue_get_state(queue_id);
    if (qptr == NULL)
    {
        cvmx_dprintf("ERROR: cvmx_cmd_queue_shutdown: Unable to get queue information.\n");
        return CVMX_CMD_QUEUE_INVALID_PARAM;
    }

    if (cvmx_cmd_queue_length(queue_id) > 0)
    {
        cvmx_dprintf("ERROR: cvmx_cmd_queue_shutdown: Queue still has data in it.\n");
        return CVMX_CMD_QUEUE_FULL;
    }

    __cvmx_cmd_queue_lock(queue_id, qptr);
    if (qptr->base_ptr_div128)
    {
        cvmx_fpa_free(cvmx_phys_to_ptr((uint64_t)qptr->base_ptr_div128<<7), qptr->fpa_pool, 0);
        qptr->base_ptr_div128 = 0;
    }
    __cvmx_cmd_queue_unlock(qptr);

    return CVMX_CMD_QUEUE_SUCCESS;
}