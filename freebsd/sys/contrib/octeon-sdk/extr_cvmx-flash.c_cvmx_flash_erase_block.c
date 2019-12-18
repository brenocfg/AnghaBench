#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {int vendor; scalar_t__ erase_timeout; TYPE_1__* region; } ;
struct TYPE_3__ {int start_offset; int block_size; } ;

/* Variables and functions */
#define  CFI_CMDSET_AMD_STANDARD 130 
#define  CFI_CMDSET_INTEL_EXTENDED 129 
#define  CFI_CMDSET_INTEL_STANDARD 128 
 int __cvmx_flash_read8 (int,int) ; 
 int /*<<< orphan*/  __cvmx_flash_write8 (int,int,int) ; 
 int /*<<< orphan*/  __cvmx_flash_write_cmd (int,int,int) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_get_cycle () ; 
 int /*<<< orphan*/  cvmx_spinlock_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cvmx_spinlock_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* flash_info ; 
 int /*<<< orphan*/  flash_lock ; 

int cvmx_flash_erase_block(int chip_id, int region, int block)
{
    cvmx_spinlock_lock(&flash_lock);
#if DEBUG
    cvmx_dprintf("cvmx-flash: Erasing chip %d, region %d, block %d\n",
           chip_id, region, block);
#endif

    int offset = flash_info[chip_id].region[region].start_offset +
                block * flash_info[chip_id].region[region].block_size;

    switch (flash_info[chip_id].vendor)
    {
        case CFI_CMDSET_AMD_STANDARD:
        {
            /* Send the erase sector command sequence */
            __cvmx_flash_write_cmd(chip_id, 0x00, 0xf0); /* Reset the flash chip */
            __cvmx_flash_write_cmd(chip_id, 0x555, 0xaa);
            __cvmx_flash_write_cmd(chip_id, 0x2aa, 0x55);
            __cvmx_flash_write_cmd(chip_id, 0x555, 0x80);
            __cvmx_flash_write_cmd(chip_id, 0x555, 0xaa);
            __cvmx_flash_write_cmd(chip_id, 0x2aa, 0x55);
            __cvmx_flash_write8(chip_id, offset, 0x30);

            /* Loop checking status */
            uint8_t status = __cvmx_flash_read8(chip_id, offset);
            uint64_t start_cycle = cvmx_get_cycle();
            while (1)
            {
                /* Read the status and xor it with the old status so we can
                    find toggling bits */
                uint8_t old_status = status;
                status = __cvmx_flash_read8(chip_id, offset);
                uint8_t toggle = status ^ old_status;

                /* Check if the erase in progress bit is toggling */
                if (toggle & (1<<6))
                {
                    /* Check hardware timeout */
                    if (status & (1<<5))
                    {
                        /* Chip has signalled a timeout. Reread the status */
                        old_status = __cvmx_flash_read8(chip_id, offset);
                        status = __cvmx_flash_read8(chip_id, offset);
                        toggle = status ^ old_status;

                        /* Check if the erase in progress bit is toggling */
                        if (toggle & (1<<6))
                        {
                            cvmx_dprintf("cvmx-flash: Hardware timeout erasing block\n");
                            cvmx_spinlock_unlock(&flash_lock);
                            return -1;
                        }
                        else
                            break;  /* Not toggling, erase complete */
                    }
                }
                else
                    break;  /* Not toggling, erase complete */

                if (cvmx_get_cycle() > start_cycle + flash_info[chip_id].erase_timeout)
                {
                    cvmx_dprintf("cvmx-flash: Timeout erasing block\n");
                    cvmx_spinlock_unlock(&flash_lock);
                    return -1;
                }
            }

            __cvmx_flash_write_cmd(chip_id, 0x00, 0xf0); /* Reset the flash chip */
            cvmx_spinlock_unlock(&flash_lock);
            return 0;
        }
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
        {
            /* Send the erase sector command sequence */
            __cvmx_flash_write_cmd(chip_id, 0x00, 0xff); /* Reset the flash chip */
            __cvmx_flash_write8(chip_id, offset, 0x20);
            __cvmx_flash_write8(chip_id, offset, 0xd0);

            /* Loop checking status */
            uint8_t status = __cvmx_flash_read8(chip_id, offset);
            uint64_t start_cycle = cvmx_get_cycle();
            while ((status & 0x80) == 0)
            {
                if (cvmx_get_cycle() > start_cycle + flash_info[chip_id].erase_timeout)
                {
                    cvmx_dprintf("cvmx-flash: Timeout erasing block\n");
                    cvmx_spinlock_unlock(&flash_lock);
                    return -1;
                }
                status = __cvmx_flash_read8(chip_id, offset);
            }

            /* Check the final status */
            if (status & 0x7f)
            {
                cvmx_dprintf("cvmx-flash: Hardware failure erasing block\n");
                cvmx_spinlock_unlock(&flash_lock);
                return -1;
            }

            __cvmx_flash_write_cmd(chip_id, 0x00, 0xff); /* Reset the flash chip */
            cvmx_spinlock_unlock(&flash_lock);
            return 0;
        }
    }

    cvmx_dprintf("cvmx-flash: Unsupported flash vendor\n");
    cvmx_spinlock_unlock(&flash_lock);
    return -1;
}