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
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  rx_buffer ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_ADD_IO_SEG (scalar_t__) ; 
 int /*<<< orphan*/  CVMX_CLOCK_CORE ; 
 int /*<<< orphan*/  CVMX_SRIOMAINTX_IR_SP_TX_CTRL (int) ; 
 int /*<<< orphan*/  CVMX_SRIOMAINTX_IR_SP_TX_DATA (int) ; 
 int CVMX_SRIOMAINTX_PRI_DEV_ID (int) ; 
 int CVMX_SRIOMAINTX_SEC_DEV_ID (int) ; 
 int CVMX_SRIO_CONFIG_PRIORITY ; 
 int CVMX_SRIO_INITIALIZE_DEBUG ; 
 int /*<<< orphan*/  CVMX_SRIO_READ_MODE_MAINTENANCE ; 
 int /*<<< orphan*/  CVMX_SRIO_WRITE_MODE_MAINTENANCE ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_X ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int __cvmx_srio_local_read32 (int,int,int*) ; 
 int /*<<< orphan*/  __cvmx_srio_local_write32 (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* __cvmx_srio_state ; 
 scalar_t__ cvmx_clock_get_count (int /*<<< orphan*/ ) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int cvmx_read64_uint32 (int /*<<< orphan*/ ) ; 
 scalar_t__ cvmx_srio_physical_map (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  cvmx_srio_physical_unmap (scalar_t__,int) ; 
 int cvmx_srio_receive_spf (int,char*,int) ; 

int cvmx_srio_config_read32(int srio_port, int srcid_index, int destid,
                            int is16bit, uint8_t hopcount, uint32_t offset,
                            uint32_t *result)
{
    if (destid == -1)
    {
        int status = __cvmx_srio_local_read32(srio_port, offset, result);

        if ((status == 0) && (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG))
            cvmx_dprintf("SRIO%d: Local read [0x%06x] <= 0x%08x\n", srio_port, (unsigned int)offset, (unsigned int)*result);

        return status;
    }
    else
    {
        if (OCTEON_IS_MODEL(OCTEON_CN63XX_PASS1_X))
        {
            int return_code;
            uint32_t pkt = 0;
            uint32_t sourceid;
            uint64_t stop_cycle;
            char rx_buffer[64];

            /* Tell the user */
            if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                cvmx_dprintf("SRIO%d: Remote read [id=0x%04x hop=%3d offset=0x%06x] <= ", srio_port, destid, hopcount, (unsigned int)offset);

            /* Read the proper source ID */
            if (srcid_index)
                __cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_SEC_DEV_ID(srio_port), &sourceid);
            else
                __cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_PRI_DEV_ID(srio_port), &sourceid);

            if (is16bit)
            {
                /* Use the 16bit source ID */
                sourceid &= 0xffff;

                /* MAINT Reads are 11 bytes */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_CTRL(srio_port), 11<<16);

                pkt |= CVMX_SRIO_CONFIG_PRIORITY << 30; /* priority [31:30] */
                pkt |= 1 << 28;                         /* tt       [29:28] */
                pkt |= 0x8 << 24;                       /* ftype    [27:24] */
                pkt |= destid << 8;                     /* destID   [23:8] */
                pkt |= sourceid >> 8;                   /* sourceID [7:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= sourceid << 24;                  /* sourceID [31:24] */
                pkt |= 0 << 20;                         /* transaction [23:20] */
                pkt |= 8 << 16;                         /* rdsize [19:16] */
                pkt |= 0xc0 << 8;                       /* srcTID [15:8] */
                pkt |= hopcount;                        /* hopcount [7:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= offset << 8;                     /* offset [31:11, wdptr[10], reserved[9:8] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
            }
            else
            {
                /* Use the 8bit source ID */
                sourceid = (sourceid >> 16) & 0xff;

                /* MAINT Reads are 9 bytes */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_CTRL(srio_port), 9<<16);

                pkt |= CVMX_SRIO_CONFIG_PRIORITY << 30; /* priority [31:30] */
                pkt |= 0 << 28;                         /* tt       [29:28] */
                pkt |= 0x8 << 24;                       /* ftype    [27:24] */
                pkt |= destid << 16;                    /* destID   [23:16] */
                pkt |= sourceid << 8;                   /* sourceID [15:8] */
                pkt |= 0 << 4;                          /* transaction [7:4] */
                pkt |= 8 << 0;                          /* rdsize [3:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= 0xc0 << 24;                      /* srcTID [31:24] */
                pkt |= hopcount << 16;                  /* hopcount [23:16] */
                pkt |= offset >> 8;                     /* offset [15:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= offset << 24;                    /* offset [31:27, wdptr[26], reserved[25:24] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
            }

            stop_cycle = cvmx_clock_get_rate(CVMX_CLOCK_CORE)/10 + cvmx_clock_get_count(CVMX_CLOCK_CORE);
            do
            {
                return_code = cvmx_srio_receive_spf(srio_port, rx_buffer, sizeof(rx_buffer));
                if ((return_code == 0) && (cvmx_clock_get_count(CVMX_CLOCK_CORE) > stop_cycle))
                {
                    if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                        cvmx_dprintf("timeout\n");
                    return_code = -1;
                }
            } while (return_code == 0);

            if (return_code == ((is16bit) ? 23 : 19))
            {
                if (is16bit)
                {
                    if (offset & 4)
                        *result = *(uint32_t*)(rx_buffer + 15);
                    else
                        *result = *(uint32_t*)(rx_buffer + 11);
                }
                else
                {
                    if (offset & 4)
                        *result = *(uint32_t*)(rx_buffer + 13);
                    else
                        *result = *(uint32_t*)(rx_buffer + 9);
                }
                if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                    cvmx_dprintf("0x%08x\n", (unsigned int)*result);
                return_code = 0;
            }
            else
            {
                *result = 0xffffffff;
                return_code = -1;
            }

            return return_code;
        }
        else
        {
#if !defined(CVMX_BUILD_FOR_LINUX_HOST)
            uint64_t physical;
            physical = cvmx_srio_physical_map(srio_port,
                CVMX_SRIO_WRITE_MODE_MAINTENANCE, CVMX_SRIO_CONFIG_PRIORITY,
                CVMX_SRIO_READ_MODE_MAINTENANCE, CVMX_SRIO_CONFIG_PRIORITY,
                srcid_index, destid, is16bit, offset + (hopcount<<24), 4);
            if (!physical)
                return -1;

            if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                cvmx_dprintf("SRIO%d: Remote read [id=0x%04x hop=%3d offset=0x%06x] <= ", srio_port, destid, hopcount, (unsigned int)offset);

            /* Finally do the maintenance read to complete the config request */
            *result = cvmx_read64_uint32(CVMX_ADD_IO_SEG(physical));
            cvmx_srio_physical_unmap(physical, 4);

            if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                cvmx_dprintf("0x%08x\n", (unsigned int)*result);

            return 0;
#else
            return -1;
#endif
        }
    }
}