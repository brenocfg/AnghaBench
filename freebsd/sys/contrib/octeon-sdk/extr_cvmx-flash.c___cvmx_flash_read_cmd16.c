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
typedef  int uint16_t ;

/* Variables and functions */
 int __cvmx_flash_read_cmd (int,int) ; 

__attribute__((used)) static uint16_t __cvmx_flash_read_cmd16(int chip_id, int offset)
{
    uint16_t v = __cvmx_flash_read_cmd(chip_id, offset);
    v |= __cvmx_flash_read_cmd(chip_id, offset + 1)<<8;
    return v;
}