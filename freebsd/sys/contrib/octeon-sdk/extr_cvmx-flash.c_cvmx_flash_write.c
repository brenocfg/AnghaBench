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
struct TYPE_5__ {void* base_ptr; int size; TYPE_1__* region; } ;
typedef  TYPE_2__ cvmx_flash_t ;
struct TYPE_4__ {int num_blocks; int block_size; int start_offset; } ;

/* Variables and functions */
 int MAX_NUM_FLASH_CHIPS ; 
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 scalar_t__ cvmx_flash_erase_block (int,int,int) ; 
 scalar_t__ cvmx_flash_write_block (int,int,int,void const*) ; 
 TYPE_2__* flash_info ; 

int cvmx_flash_write(void *address, const void *data, int len)
{
    int chip_id;

    /* Find which chip controls this address. Don't allow the write to span
        multiple chips */
    for (chip_id=0; chip_id<MAX_NUM_FLASH_CHIPS; chip_id++)
    {
        if ((flash_info[chip_id].base_ptr <= address) &&
            (flash_info[chip_id].base_ptr + flash_info[chip_id].size >= address + len))
            break;
    }

    if (chip_id == MAX_NUM_FLASH_CHIPS)
    {
        cvmx_dprintf("cvmx-flash: Unable to find chip that contains address %p\n", address);
        return -1;
    }

    cvmx_flash_t *flash = flash_info + chip_id;

    /* Determine which block region we need to start writing to */
    void *region_base = flash->base_ptr;
    int region = 0;
    while (region_base + flash->region[region].num_blocks * flash->region[region].block_size <= address)
    {
        region++;
        region_base = flash->base_ptr + flash->region[region].start_offset;
    }

    /* Determine which block in the region to start at */
    int block = (address - region_base) / flash->region[region].block_size;

    /* Require all writes to start on block boundries */
    if (address != region_base + block*flash->region[region].block_size)
    {
        cvmx_dprintf("cvmx-flash: Write address not aligned on a block boundry\n");
        return -1;
    }

    /* Loop until we're out of data */
    while (len > 0)
    {
        /* Erase the current block */
        if (cvmx_flash_erase_block(chip_id, region, block))
            return -1;
        /* Write the new data */
        if (cvmx_flash_write_block(chip_id, region, block, data))
            return -1;

        /* Increment to the next block */
        data += flash->region[region].block_size;
        len -= flash->region[region].block_size;
        block++;
        if (block >= flash->region[region].num_blocks)
        {
            block = 0;
            region++;
        }
    }

    return 0;
}