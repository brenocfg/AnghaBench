#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  cvmx_dprintf (char*,...) ; 
 int* cvmx_phys_to_ptr (int /*<<< orphan*/ ) ; 
 int debug_indent ; 

__attribute__((used)) static void __cvmx_nand_hex_dump(uint64_t buffer_address, int buffer_length)
{
    uint8_t *buffer = cvmx_phys_to_ptr(buffer_address);
    int offset = 0;
    while (offset < buffer_length)
    {
        int i;
        cvmx_dprintf("%*s%04x:",  2*debug_indent, "", offset);
        for (i=0; i<32; i++)
        {
            if ((i&3) == 0)
                cvmx_dprintf(" ");
            if (offset+i < buffer_length)
                cvmx_dprintf("%02x", 0xff & buffer[offset+i]);
            else
                cvmx_dprintf("  ");
        }
        cvmx_dprintf("\n");
        offset += 32;
    }
}