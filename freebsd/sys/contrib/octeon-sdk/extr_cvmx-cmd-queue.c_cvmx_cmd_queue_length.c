#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int doorbell; } ;
struct TYPE_15__ {TYPE_1__ cn38xx; void* u64; } ;
typedef  TYPE_6__ cvmx_pko_mem_debug9_t ;
struct TYPE_12__ {int doorbell; } ;
struct TYPE_11__ {int doorbell; } ;
struct TYPE_16__ {TYPE_3__ cn58xx; TYPE_2__ cn68xx; void* u64; } ;
typedef  TYPE_7__ cvmx_pko_mem_debug8_t ;
struct TYPE_13__ {int dbell; } ;
struct TYPE_17__ {TYPE_4__ s; void* u64; } ;
typedef  TYPE_8__ cvmx_npei_dmax_counts_t ;
struct TYPE_14__ {int dbell; } ;
struct TYPE_18__ {TYPE_5__ s; void* u64; } ;
typedef  TYPE_9__ cvmx_dpi_dmax_counts_t ;
typedef  int cvmx_cmd_queue_id_t ;

/* Variables and functions */
#define  CVMX_CMD_QUEUE_DFA 133 
#define  CVMX_CMD_QUEUE_DMA_BASE 132 
#define  CVMX_CMD_QUEUE_END 131 
 int CVMX_CMD_QUEUE_INVALID_PARAM ; 
#define  CVMX_CMD_QUEUE_PKO_BASE 130 
#define  CVMX_CMD_QUEUE_RAID 129 
#define  CVMX_CMD_QUEUE_ZIP 128 
 int /*<<< orphan*/  CVMX_DPI_DMAX_COUNTS (int) ; 
 scalar_t__ CVMX_ENABLE_PARAMETER_CHECKING ; 
 int /*<<< orphan*/  CVMX_PEXP_NPEI_DMAX_COUNTS (int) ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_DEBUG8 ; 
 int /*<<< orphan*/  CVMX_PKO_MEM_DEBUG9 ; 
 int /*<<< orphan*/  CVMX_PKO_REG_READ_IDX ; 
 int /*<<< orphan*/  OCTEON_CN3XXX ; 
 int /*<<< orphan*/  OCTEON_FEATURE_NPEI ; 
 int /*<<< orphan*/  OCTEON_FEATURE_PKND ; 
 int /*<<< orphan*/  OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __cvmx_cmd_queue_get_state (int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  octeon_has_feature (int /*<<< orphan*/ ) ; 

int cvmx_cmd_queue_length(cvmx_cmd_queue_id_t queue_id)
{
    if (CVMX_ENABLE_PARAMETER_CHECKING)
    {
        if (__cvmx_cmd_queue_get_state(queue_id) == NULL)
            return CVMX_CMD_QUEUE_INVALID_PARAM;
    }

    /* The cast is here so gcc with check that all values in the
        cvmx_cmd_queue_id_t enumeration are here */
    switch ((cvmx_cmd_queue_id_t)(queue_id & 0xff0000))
    {
        case CVMX_CMD_QUEUE_PKO_BASE:
            /* FIXME: Need atomic lock on CVMX_PKO_REG_READ_IDX. Right now we
                are normally called with the queue lock, so that is a SLIGHT
                amount of protection */
            cvmx_write_csr(CVMX_PKO_REG_READ_IDX, queue_id & 0xffff);
            if (OCTEON_IS_MODEL(OCTEON_CN3XXX))
            {
                cvmx_pko_mem_debug9_t debug9;
                debug9.u64 = cvmx_read_csr(CVMX_PKO_MEM_DEBUG9);
                return debug9.cn38xx.doorbell;
            }
            else
            {
                cvmx_pko_mem_debug8_t debug8;
                debug8.u64 = cvmx_read_csr(CVMX_PKO_MEM_DEBUG8);
                if (octeon_has_feature(OCTEON_FEATURE_PKND))
                    return debug8.cn68xx.doorbell;
                else
                    return debug8.cn58xx.doorbell;
            }
        case CVMX_CMD_QUEUE_ZIP:
        case CVMX_CMD_QUEUE_DFA:
        case CVMX_CMD_QUEUE_RAID:
            // FIXME: Implement other lengths
            return 0;
        case CVMX_CMD_QUEUE_DMA_BASE:
            if (octeon_has_feature(OCTEON_FEATURE_NPEI))
            {
                cvmx_npei_dmax_counts_t dmax_counts;
                dmax_counts.u64 = cvmx_read_csr(CVMX_PEXP_NPEI_DMAX_COUNTS(queue_id & 0x7));
                return dmax_counts.s.dbell;
            }
            else
            {
                cvmx_dpi_dmax_counts_t dmax_counts;
                dmax_counts.u64 = cvmx_read_csr(CVMX_DPI_DMAX_COUNTS(queue_id & 0x7));
                return dmax_counts.s.dbell;
            }
        case CVMX_CMD_QUEUE_END:
            return CVMX_CMD_QUEUE_INVALID_PARAM;
    }
    return CVMX_CMD_QUEUE_INVALID_PARAM;
}