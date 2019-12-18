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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */

__attribute__((used)) static void __cvmx_nand_fixup_16bit_id_reads(uint8_t *buf, int buffer_length)
{
    /* Decimate data, taking only every other byte. */
    int i;
    for (i = 0; i < buffer_length/2; i++)
        buf[i] = buf[2*i + 1];
}