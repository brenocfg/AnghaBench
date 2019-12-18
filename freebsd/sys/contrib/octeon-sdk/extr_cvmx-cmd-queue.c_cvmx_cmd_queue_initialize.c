#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  enb; } ;
struct TYPE_8__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_2__ cvmx_fpa_ctl_status_t ;
typedef  scalar_t__ cvmx_cmd_queue_result_t ;
typedef  int /*<<< orphan*/  cvmx_cmd_queue_id_t ;
struct TYPE_9__ {int base_ptr_div128; int max_depth; int fpa_pool; int pool_size_m1; } ;
typedef  TYPE_3__ __cvmx_cmd_queue_state_t ;
struct TYPE_10__ {scalar_t__* ticket; } ;

/* Variables and functions */
 scalar_t__ CVMX_CMD_QUEUE_ALREADY_SETUP ; 
 scalar_t__ CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH ; 
 scalar_t__ CVMX_CMD_QUEUE_INVALID_PARAM ; 
 scalar_t__ CVMX_CMD_QUEUE_NO_MEMORY ; 
 scalar_t__ CVMX_CMD_QUEUE_SUCCESS ; 
 int /*<<< orphan*/  CVMX_FPA_CTL_STATUS ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 size_t __cvmx_cmd_queue_get_index (int /*<<< orphan*/ ) ; 
 TYPE_3__* __cvmx_cmd_queue_get_state (int /*<<< orphan*/ ) ; 
 scalar_t__ __cvmx_cmd_queue_init_state_ptr () ; 
 TYPE_5__* __cvmx_cmd_queue_state_ptr ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 void* cvmx_fpa_alloc (int) ; 
 int cvmx_ptr_to_phys (void*) ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

cvmx_cmd_queue_result_t cvmx_cmd_queue_initialize(cvmx_cmd_queue_id_t queue_id, int max_depth, int fpa_pool, int pool_size)
{
    __cvmx_cmd_queue_state_t *qstate;
    cvmx_cmd_queue_result_t result = __cvmx_cmd_queue_init_state_ptr();
    if (result != CVMX_CMD_QUEUE_SUCCESS)
        return result;

    qstate = __cvmx_cmd_queue_get_state(queue_id);
    if (qstate == NULL)
        return CVMX_CMD_QUEUE_INVALID_PARAM;

    /* We artificially limit max_depth to 1<<20 words. It is an arbitrary limit */
    if (CVMX_CMD_QUEUE_ENABLE_MAX_DEPTH)
    {
        if ((max_depth < 0) || (max_depth > 1<<20))
            return CVMX_CMD_QUEUE_INVALID_PARAM;
    }
    else if (max_depth != 0)
        return CVMX_CMD_QUEUE_INVALID_PARAM;

    if ((fpa_pool < 0) || (fpa_pool > 7))
        return CVMX_CMD_QUEUE_INVALID_PARAM;
    if ((pool_size < 128) || (pool_size > 65536))
        return CVMX_CMD_QUEUE_INVALID_PARAM;

    /* See if someone else has already initialized the queue */
    if (qstate->base_ptr_div128)
    {
        if (max_depth != (int)qstate->max_depth)
        {
            cvmx_dprintf("ERROR: cvmx_cmd_queue_initialize: Queue already initialized with different max_depth (%d).\n", (int)qstate->max_depth);
            return CVMX_CMD_QUEUE_INVALID_PARAM;
        }
        if (fpa_pool != qstate->fpa_pool)
        {
            cvmx_dprintf("ERROR: cvmx_cmd_queue_initialize: Queue already initialized with different FPA pool (%u).\n", qstate->fpa_pool);
            return CVMX_CMD_QUEUE_INVALID_PARAM;
        }
        if ((pool_size>>3)-1 != qstate->pool_size_m1)
        {
            cvmx_dprintf("ERROR: cvmx_cmd_queue_initialize: Queue already initialized with different FPA pool size (%u).\n", (qstate->pool_size_m1+1)<<3);
            return CVMX_CMD_QUEUE_INVALID_PARAM;
        }
        CVMX_SYNCWS;
        return CVMX_CMD_QUEUE_ALREADY_SETUP;
    }
    else
    {
        cvmx_fpa_ctl_status_t status;
        void *buffer;

        status.u64 = cvmx_read_csr(CVMX_FPA_CTL_STATUS);
        if (!status.s.enb)
        {
            cvmx_dprintf("ERROR: cvmx_cmd_queue_initialize: FPA is not enabled.\n");
            return CVMX_CMD_QUEUE_NO_MEMORY;
        }
        buffer = cvmx_fpa_alloc(fpa_pool);
        if (buffer == NULL)
        {
            cvmx_dprintf("ERROR: cvmx_cmd_queue_initialize: Unable to allocate initial buffer.\n");
            return CVMX_CMD_QUEUE_NO_MEMORY;
        }

        memset(qstate, 0, sizeof(*qstate));
        qstate->max_depth = max_depth;
        qstate->fpa_pool = fpa_pool;
        qstate->pool_size_m1 = (pool_size>>3)-1;
        qstate->base_ptr_div128 = cvmx_ptr_to_phys(buffer) / 128;
        /* We zeroed the now serving field so we need to also zero the ticket */
        __cvmx_cmd_queue_state_ptr->ticket[__cvmx_cmd_queue_get_index(queue_id)] = 0;
        CVMX_SYNCWS;
        return CVMX_CMD_QUEUE_SUCCESS;
    }
}