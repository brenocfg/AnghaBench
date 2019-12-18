#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {scalar_t__ ircnt; } ;
struct TYPE_10__ {TYPE_1__ s; int /*<<< orphan*/  u64; } ;
typedef  TYPE_4__ cvmx_mixx_ircnt_t ;
struct TYPE_11__ {size_t rx_read_index; int /*<<< orphan*/  lock; TYPE_3__* rx_ring; scalar_t__* rx_buffers; } ;
typedef  TYPE_5__ cvmx_mgmt_port_state_t ;
struct TYPE_8__ {int code; int len; } ;
struct TYPE_9__ {TYPE_2__ s; } ;

/* Variables and functions */
 int CVMX_MGMT_PORT_INVALID_PARAM ; 
 int CVMX_MGMT_PORT_NO_MEMORY ; 
 int CVMX_MGMT_PORT_NUM_RX_BUFFERS ; 
 int CVMX_MGMT_PORT_RX_BUFFER_SIZE ; 
 int /*<<< orphan*/  CVMX_MIXX_IRCNT (int) ; 
 int /*<<< orphan*/  CVMX_MIXX_IRING2 (int) ; 
 int /*<<< orphan*/  CVMX_SYNCWS ; 
 int /*<<< orphan*/  OCTEON_CN56XX_PASS1_X ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int __cvmx_mgmt_port_num_ports () ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_link_get (int) ; 
 int /*<<< orphan*/  cvmx_mgmt_port_link_set (int,int /*<<< orphan*/ ) ; 
 TYPE_5__* cvmx_mgmt_port_state_ptr ; 
 int /*<<< orphan*/  cvmx_read_csr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,scalar_t__*,int) ; 

int cvmx_mgmt_port_receive(int port, int buffer_len, uint8_t *buffer)
{
    cvmx_mixx_ircnt_t mix_ircnt;
    cvmx_mgmt_port_state_t *state;
    int result;

    if ((port < 0) || (port >= __cvmx_mgmt_port_num_ports()))
        return CVMX_MGMT_PORT_INVALID_PARAM;

    /* Max sure the buffer size is valid */
    if (buffer_len < 1)
        return CVMX_MGMT_PORT_INVALID_PARAM;

    if (buffer == NULL)
        return CVMX_MGMT_PORT_INVALID_PARAM;

    state = cvmx_mgmt_port_state_ptr + port;

    cvmx_spinlock_lock(&state->lock);

    /* Find out how many RX packets are pending */
    mix_ircnt.u64 = cvmx_read_csr(CVMX_MIXX_IRCNT(port));
    if (mix_ircnt.s.ircnt)
    {
        uint64_t *source = (void *)state->rx_buffers[state->rx_read_index];
	uint64_t *zero_check = source;
        /* CN56XX pass 1 has an errata where packets might start 8 bytes
            into the buffer instead of at their correct lcoation. If the
            first 8 bytes is zero we assume this has happened */
        if (OCTEON_IS_MODEL(OCTEON_CN56XX_PASS1_X) && (*zero_check == 0))
            source++;
        /* Start off with zero bytes received */
        result = 0;
        /* While the completion code signals more data, copy the buffers
            into the user's data */
        while (state->rx_ring[state->rx_read_index].s.code == 16)
        {
            /* Only copy what will fit in the user's buffer */
            int length = state->rx_ring[state->rx_read_index].s.len;
            if (length > buffer_len)
                length = buffer_len;
            memcpy(buffer, source, length);
            /* Reduce the size of the buffer to the remaining space. If we run
                out we will signal an error when the code 15 buffer doesn't fit */
            buffer += length;
            buffer_len -= length;
            result += length;
            /* Update this buffer for reuse in future receives. This size is
                -8 due to an errata for CN56XX pass 1 */
            state->rx_ring[state->rx_read_index].s.code = 0;
            state->rx_ring[state->rx_read_index].s.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
            state->rx_read_index = (state->rx_read_index + 1) % CVMX_MGMT_PORT_NUM_RX_BUFFERS;
            /* Zero the beginning of the buffer for use by the errata check */
            *zero_check = 0;
            CVMX_SYNCWS;
            /* Increment the number of RX buffers */
            cvmx_write_csr(CVMX_MIXX_IRING2(port), 1);
            source = (void *)state->rx_buffers[state->rx_read_index];
            zero_check = source;
        }

        /* Check for the final good completion code */
        if (state->rx_ring[state->rx_read_index].s.code == 15)
        {
            if (buffer_len >= state->rx_ring[state->rx_read_index].s.len)
            {
                int length = state->rx_ring[state->rx_read_index].s.len;
                memcpy(buffer, source, length);
                result += length;
            }
            else
            {
                /* Not enough room for the packet */
                cvmx_dprintf("ERROR: cvmx_mgmt_port_receive: Packet (%d) larger than supplied buffer (%d)\n", state->rx_ring[state->rx_read_index].s.len, buffer_len);
                result = CVMX_MGMT_PORT_NO_MEMORY;
            }
        }
        else
        {
            cvmx_dprintf("ERROR: cvmx_mgmt_port_receive: Receive error code %d. Packet dropped(Len %d), \n",
                         state->rx_ring[state->rx_read_index].s.code, state->rx_ring[state->rx_read_index].s.len + result);
            result = -state->rx_ring[state->rx_read_index].s.code;


            /* Check to see if we need to change the duplex. */
            cvmx_mgmt_port_link_set(port, cvmx_mgmt_port_link_get(port));
        }

        /* Clean out the ring buffer entry. This size is -8 due to an errata
            for CN56XX pass 1 */
        state->rx_ring[state->rx_read_index].s.code = 0;
        state->rx_ring[state->rx_read_index].s.len = CVMX_MGMT_PORT_RX_BUFFER_SIZE - 8;
        state->rx_read_index = (state->rx_read_index + 1) % CVMX_MGMT_PORT_NUM_RX_BUFFERS;
        /* Zero the beginning of the buffer for use by the errata check */
        *zero_check = 0;
        CVMX_SYNCWS;
        /* Increment the number of RX buffers */
        cvmx_write_csr(CVMX_MIXX_IRING2(port), 1);
        /* Decrement the pending RX count */
        cvmx_write_csr(CVMX_MIXX_IRCNT(port), 1);
    }
    else
    {
        /* No packets available */
        result = 0;
    }
    cvmx_spinlock_unlock(&state->lock);
    return result;
}