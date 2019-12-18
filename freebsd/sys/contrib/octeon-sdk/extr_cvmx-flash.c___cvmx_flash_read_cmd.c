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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ is_16bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  __cvmx_flash_read8 (int,int) ; 
 TYPE_1__* flash_info ; 

__attribute__((used)) static uint8_t __cvmx_flash_read_cmd(int chip_id, int offset)
{
    if (flash_info[chip_id].is_16bit)
        offset<<=1;
    return __cvmx_flash_read8(chip_id, offset);
}