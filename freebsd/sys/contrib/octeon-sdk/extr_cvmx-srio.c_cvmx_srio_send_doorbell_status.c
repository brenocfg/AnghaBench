#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pending; } ;
struct TYPE_11__ {TYPE_1__ s; void* u64; } ;
typedef  TYPE_4__ cvmx_sriox_tx_bell_t ;
struct TYPE_9__ {scalar_t__ retry; scalar_t__ error; scalar_t__ timeout; } ;
struct TYPE_12__ {TYPE_2__ s; void* u64; } ;
typedef  TYPE_5__ cvmx_sriox_tx_bell_info_t ;
struct TYPE_10__ {scalar_t__ txbell; scalar_t__ bell_err; } ;
struct TYPE_13__ {TYPE_3__ s; void* u64; } ;
typedef  TYPE_6__ cvmx_sriox_int_reg_t ;
typedef  int /*<<< orphan*/  cvmx_srio_doorbell_status_t ;
struct TYPE_14__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SRIOX_INT_REG (int) ; 
 int /*<<< orphan*/  CVMX_SRIOX_TX_BELL (int) ; 
 int /*<<< orphan*/  CVMX_SRIOX_TX_BELL_INFO (int) ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_BUSY ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_DONE ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_ERROR ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_NONE ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_RETRY ; 
 int /*<<< orphan*/  CVMX_SRIO_DOORBELL_TMOUT ; 
 int CVMX_SRIO_INITIALIZE_DEBUG ; 
 TYPE_7__* __cvmx_srio_state ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int) ; 
 void* cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,void*) ; 

cvmx_srio_doorbell_status_t cvmx_srio_send_doorbell_status(int srio_port)
{
    cvmx_sriox_tx_bell_t tx_bell;
    cvmx_sriox_tx_bell_info_t tx_bell_info;
    cvmx_sriox_int_reg_t int_reg;
    cvmx_sriox_int_reg_t int_reg_clear;

    /* Return busy if the doorbell is still processing */
    tx_bell.u64 = cvmx_read_csr(CVMX_SRIOX_TX_BELL(srio_port));
    if (tx_bell.s.pending)
        return CVMX_SRIO_DOORBELL_BUSY;

    /* Read and clear the TX doorbell interrupts */
    int_reg.u64 = cvmx_read_csr(CVMX_SRIOX_INT_REG(srio_port));
    int_reg_clear.u64 = 0;
    int_reg_clear.s.bell_err = int_reg.s.bell_err;
    int_reg_clear.s.txbell = int_reg.s.txbell;
    cvmx_write_csr(CVMX_SRIOX_INT_REG(srio_port), int_reg_clear.u64);

    /* Check for errors */
    if (int_reg.s.bell_err)
    {
        if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
            cvmx_dprintf("SRIO%d: Send doorbell failed\n", srio_port);
        tx_bell_info.u64 = cvmx_read_csr(CVMX_SRIOX_TX_BELL_INFO(srio_port));
        if (tx_bell_info.s.timeout)
            return CVMX_SRIO_DOORBELL_TMOUT;
        if (tx_bell_info.s.error)
            return CVMX_SRIO_DOORBELL_ERROR;
        if (tx_bell_info.s.retry)
            return CVMX_SRIO_DOORBELL_RETRY;
    }

    /* Check if we're done */
    if (int_reg.s.txbell)
        return CVMX_SRIO_DOORBELL_DONE;

    /* No doorbell found */
    return CVMX_SRIO_DOORBELL_NONE;
}