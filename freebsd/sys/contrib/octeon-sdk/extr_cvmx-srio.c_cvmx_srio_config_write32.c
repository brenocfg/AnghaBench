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
 int CVMX_SRIOMAINTX_IR_SP_TX_CTRL (int) ; 
 int CVMX_SRIOMAINTX_IR_SP_TX_DATA (int) ; 
 int /*<<< orphan*/  CVMX_SRIOMAINTX_PRI_DEV_ID (int) ; 
 int /*<<< orphan*/  CVMX_SRIOMAINTX_SEC_DEV_ID (int) ; 
 int CVMX_SRIO_CONFIG_PRIORITY ; 
 int CVMX_SRIO_INITIALIZE_DEBUG ; 
 int /*<<< orphan*/  CVMX_SRIO_READ_MODE_MAINTENANCE ; 
 int /*<<< orphan*/  CVMX_SRIO_WRITE_MODE_MAINTENANCE ; 
 int /*<<< orphan*/  OCTEON_CN63XX_PASS1_X ; 
 scalar_t__ OCTEON_IS_MODEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __cvmx_srio_local_read32 (int,int /*<<< orphan*/ ,int*) ; 
 int __cvmx_srio_local_write32 (int,int,int) ; 
 TYPE_1__* __cvmx_srio_state ; 
 scalar_t__ cvmx_clock_get_count (int /*<<< orphan*/ ) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_srio_physical_map (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int,int,int,int,int) ; 
 int cvmx_srio_physical_unmap (scalar_t__,int) ; 
 int cvmx_srio_receive_spf (int,char*,int) ; 
 int /*<<< orphan*/  cvmx_write64_uint32 (int /*<<< orphan*/ ,int) ; 

int cvmx_srio_config_write32(int srio_port, int srcid_index, int destid,
                             int is16bit, uint8_t hopcount, uint32_t offset,
                             uint32_t data)
{
    if (destid == -1)
    {
        if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
            cvmx_dprintf("SRIO%d: Local write[0x%06x] => 0x%08x\n", srio_port, (unsigned int)offset, (unsigned int)data);

        return __cvmx_srio_local_write32(srio_port, offset, data);
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
                cvmx_dprintf("SRIO%d: Remote write[id=0x%04x hop=%3d offset=0x%06x] => 0x%08x\n", srio_port, destid, hopcount, (unsigned int)offset, (unsigned int)data);

            /* Read the proper source ID */
            if (srcid_index)
                __cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_SEC_DEV_ID(srio_port), &sourceid);
            else
                __cvmx_srio_local_read32(srio_port, CVMX_SRIOMAINTX_PRI_DEV_ID(srio_port), &sourceid);

            if (is16bit)
            {
                /* Use the 16bit source ID */
                sourceid &= 0xffff;

                /* MAINT Writes are 19 bytes */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_CTRL(srio_port), 19<<16);

                pkt |= CVMX_SRIO_CONFIG_PRIORITY << 30; /* priority [31:30] */
                pkt |= 1 << 28;                         /* tt       [29:28] */
                pkt |= 0x8 << 24;                       /* ftype    [27:24] */
                pkt |= destid << 8;                     /* destID   [23:8] */
                pkt |= sourceid >> 8;                   /* sourceID [7:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= sourceid << 24;                  /* sourceID [31:24] */
                pkt |= 1 << 20;                         /* transaction [23:20] */
                pkt |= 8 << 16;                         /* wrsize [19:16] */
                pkt |= 0xc0 << 8;                       /* srcTID [15:8] */
                pkt |= hopcount;                        /* hopcount [7:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= offset << 8;                     /* offset [31:11, wdptr[10], reserved[9:8] */
                if ((offset & 4) == 0)
                    pkt |= 0xff & (data >> 24);       /* data [7:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                if (offset & 4)
                {
                    pkt = 0xff & (data >> 24);
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    pkt = data << 8;
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                }
                else
                {
                    pkt = data << 8;
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), 0);
                }
            }
            else
            {
                /* Use the 8bit source ID */
                sourceid = (sourceid >> 16) & 0xff;

                /* MAINT Writes are 17 bytes */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_CTRL(srio_port), 17<<16);

                pkt |= CVMX_SRIO_CONFIG_PRIORITY << 30; /* priority [31:30] */
                pkt |= 0 << 28;                         /* tt       [29:28] */
                pkt |= 0x8 << 24;                       /* ftype    [27:24] */
                pkt |= destid << 16;                    /* destID   [23:16] */
                pkt |= sourceid << 8;                   /* sourceID [15:8] */
                pkt |= 1 << 4;                          /* transaction [7:4] */
                pkt |= 8 << 0;                          /* wrsize [3:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= 0xc0 << 24;                      /* srcTID [31:24] */
                pkt |= hopcount << 16;                  /* hopcount [23:16] */
                pkt |= offset >> 8;                     /* offset [15:0] */
                __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                pkt = 0;
                pkt |= offset << 24;                    /* offset [31:27, wdptr[26], reserved[25:24] */
                if (offset & 4)
                {
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    pkt = data >> 8;
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    pkt = data << 24;
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                }
                else
                {
                    pkt |= data >> 8;                    /* data [23:0] */
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    pkt = data << 24;                    /* data [31:24] */
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), pkt);
                    __cvmx_srio_local_write32(srio_port, CVMX_SRIOMAINTX_IR_SP_TX_DATA(srio_port), 0);
                }
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

            if (return_code == ((is16bit) ? 15 : 11))
                return_code = 0;
            else
            {
                cvmx_dprintf("SRIO%d: Remote write failed\n", srio_port);
                return_code = -1;
            }

            return return_code;
        }
        else
        {
#if !defined(CVMX_BUILD_FOR_LINUX_HOST)
            uint64_t physical = cvmx_srio_physical_map(srio_port,
                    CVMX_SRIO_WRITE_MODE_MAINTENANCE, CVMX_SRIO_CONFIG_PRIORITY,
                    CVMX_SRIO_READ_MODE_MAINTENANCE, CVMX_SRIO_CONFIG_PRIORITY,
                    srcid_index, destid, is16bit, offset + (hopcount<<24), 4);
            if (!physical)
                return -1;

            if (__cvmx_srio_state[srio_port].flags & CVMX_SRIO_INITIALIZE_DEBUG)
                cvmx_dprintf("SRIO%d: Remote write[id=0x%04x hop=%3d offset=0x%06x] => 0x%08x\n", srio_port, destid, hopcount, (unsigned int)offset, (unsigned int)data);

            /* Finally do the maintenance write to complete the config request */
            cvmx_write64_uint32(CVMX_ADD_IO_SEG(physical), data);
            return cvmx_srio_physical_unmap(physical, 4);
#else
            return -1;
#endif
        }
    }
}