#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint16_t ;
struct TYPE_4__ {int is_16bit; int vendor; unsigned long long write_timeout; unsigned long long erase_timeout; int size; int num_regions; TYPE_2__* region; int /*<<< orphan*/ * base_ptr; } ;
typedef  TYPE_1__ cvmx_flash_t ;
struct TYPE_5__ {int start_offset; unsigned int num_blocks; int block_size; } ;
typedef  TYPE_2__ cvmx_flash_region_t ;

/* Variables and functions */
#define  CFI_CMDSET_AMD_STANDARD 130 
#define  CFI_CMDSET_INTEL_EXTENDED 129 
#define  CFI_CMDSET_INTEL_STANDARD 128 
 int /*<<< orphan*/  CVMX_CLOCK_CORE ; 
 int __cvmx_flash_read_cmd (int,int) ; 
 void* __cvmx_flash_read_cmd16 (int,int) ; 
 int /*<<< orphan*/  __cvmx_flash_write_cmd (int,int,int) ; 
 int cvmx_clock_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,int,int,int,int,...) ; 
 TYPE_1__* flash_info ; 

__attribute__((used)) static int __cvmx_flash_queury_cfi(int chip_id, void *base_ptr)
{
    int region;
    cvmx_flash_t *flash = flash_info + chip_id;

    /* Set the minimum needed for the read and write primitives to work */
    flash->base_ptr = base_ptr;
    flash->is_16bit = 1;   /* FIXME: Currently assumes the chip is 16bits */

    /* Put flash in CFI query mode */
    __cvmx_flash_write_cmd(chip_id, 0x00, 0xf0); /* Reset the flash chip */
    __cvmx_flash_write_cmd(chip_id, 0x55, 0x98);

    /* Make sure we get the QRY response we should */
    if ((__cvmx_flash_read_cmd(chip_id, 0x10) != 'Q') ||
        (__cvmx_flash_read_cmd(chip_id, 0x11) != 'R') ||
        (__cvmx_flash_read_cmd(chip_id, 0x12) != 'Y'))
    {
        flash->base_ptr = NULL;
        return -1;
    }

    /* Read the 16bit vendor ID */
    flash->vendor = __cvmx_flash_read_cmd16(chip_id, 0x13);

    /* Read the write timeout. The timeout is microseconds(us) is 2^0x1f
        typically. The worst case is this value time 2^0x23 */
    flash->write_timeout = 1ull << (__cvmx_flash_read_cmd(chip_id, 0x1f) +
                                    __cvmx_flash_read_cmd(chip_id, 0x23));

    /* Read the erase timeout. The timeout is milliseconds(ms) is 2^0x21
        typically. The worst case is this value time 2^0x25 */
    flash->erase_timeout = 1ull << (__cvmx_flash_read_cmd(chip_id, 0x21) +
                                    __cvmx_flash_read_cmd(chip_id, 0x25));

    /* Get the flash size. This is 2^0x27 */
    flash->size = 1<<__cvmx_flash_read_cmd(chip_id, 0x27);

    /* Get the number of different sized block regions from 0x2c */
    flash->num_regions = __cvmx_flash_read_cmd(chip_id, 0x2c);

    int start_offset = 0;
    /* Loop through all regions get information about each */
    for (region=0; region<flash->num_regions; region++)
    {
        cvmx_flash_region_t *rgn_ptr = flash->region + region;
        rgn_ptr->start_offset = start_offset;

        /* The number of blocks in each region is a 16 bit little endian
            endian field. It is encoded at 0x2d + region*4 as (blocks-1) */
        uint16_t blocks = __cvmx_flash_read_cmd16(chip_id, 0x2d + region*4);
        rgn_ptr->num_blocks =  1u + blocks;

        /* The size of each block is a 16 bit little endian endian field. It
            is encoded at 0x2d + region*4 + 2 as (size/256). Zero is a special
            case representing 128 */
        uint16_t size = __cvmx_flash_read_cmd16(chip_id, 0x2d + region*4 + 2);
        if (size == 0)
            rgn_ptr->block_size = 128;
        else
            rgn_ptr->block_size = 256u * size;

        start_offset += rgn_ptr->block_size * rgn_ptr->num_blocks;
    }

    /* Take the chip out of CFI query mode */
    switch (flash_info[chip_id].vendor)
    {
        case CFI_CMDSET_AMD_STANDARD:
            __cvmx_flash_write_cmd(chip_id, 0x00, 0xf0);
        case CFI_CMDSET_INTEL_STANDARD:
        case CFI_CMDSET_INTEL_EXTENDED:
            __cvmx_flash_write_cmd(chip_id, 0x00, 0xff);
            break;
    }

    /* Convert the timeouts to cycles */
    flash->write_timeout *= cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000000;
    flash->erase_timeout *= cvmx_clock_get_rate(CVMX_CLOCK_CORE) / 1000;

#if DEBUG
    /* Print the information about the chip */
    cvmx_dprintf("cvmx-flash: Base pointer:  %p\n"
           "            Vendor:        0x%04x\n"
           "            Size:          %d bytes\n"
           "            Num regions:   %d\n"
           "            Erase timeout: %llu cycles\n"
           "            Write timeout: %llu cycles\n",
           flash->base_ptr,
           (unsigned int)flash->vendor,
           flash->size,
           flash->num_regions,
           (unsigned long long)flash->erase_timeout,
           (unsigned long long)flash->write_timeout);

    for (region=0; region<flash->num_regions; region++)
    {
        cvmx_dprintf("            Region %d: offset 0x%x, %d blocks, %d bytes/block\n",
               region,
               flash->region[region].start_offset,
               flash->region[region].num_blocks,
               flash->region[region].block_size);
    }
#endif

    return 0;
}