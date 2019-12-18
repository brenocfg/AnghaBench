#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {int buffers; int octets; } ;
struct TYPE_5__ {TYPE_1__ s; scalar_t__ u32; } ;
typedef  TYPE_2__ cvmx_sriomaintx_ir_sp_rx_stat_t ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_SRIOMAINTX_IR_SP_RX_DATA (int) ; 
 int /*<<< orphan*/  CVMX_SRIOMAINTX_IR_SP_RX_STAT (int) ; 
 int CVMX_SRIO_INITIALIZE_DEBUG ; 
 scalar_t__ __cvmx_srio_local_read32 (int,int /*<<< orphan*/ ,scalar_t__*) ; 
 TYPE_3__* __cvmx_srio_state ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 

int cvmx_srio_receive_spf(int srio_port, void *buffer, int buffer_length)
{
    uint32_t *ptr = (uint32_t *)buffer;
    cvmx_sriomaintx_ir_sp_rx_stat_t sriomaintx_ir_sp_rx_stat;

    /* Read the SFP status */
    if (__cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_IR_SP_RX_STAT(srio_port), &sriomaintx_ir_sp_rx_stat.u32))
        return -1;

    /* Return zero if there isn't a packet available */
    if (sriomaintx_ir_sp_rx_stat.s.buffers < 1)
        return 0;

    if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
        cvmx_dprintf("SRIO%d: Soft packet FIFO received %d bytes", srio_port, sriomaintx_ir_sp_rx_stat.s.octets);

    /* Return error if the packet is larger than our buffer */
    if (sriomaintx_ir_sp_rx_stat.s.octets > buffer_length)
        return -1;

    /* Read out the packet four bytes at a time */
    buffer_length = sriomaintx_ir_sp_rx_stat.s.octets;
    while (buffer_length > 0)
    {
        __cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_IR_SP_RX_DATA(srio_port), ptr);
        if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
            cvmx_dprintf(" %08x", (unsigned int)*ptr);
        ptr++;
        buffer_length-=4;
    }

    if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
        cvmx_dprintf("\n");

    /* Return the number of bytes in the buffer */
    return sriomaintx_ir_sp_rx_stat.s.octets;
}