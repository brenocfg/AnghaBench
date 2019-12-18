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
struct TYPE_2__ {int is_16bit; scalar_t__ base_ptr; } ;

/* Variables and functions */
 TYPE_1__* flash_info ; 

__attribute__((used)) static void __cvmx_flash_write_cmd(int chip_id, int offset, uint8_t data)
{
    volatile uint8_t *flash_ptr = (volatile uint8_t *)flash_info[chip_id].base_ptr;
    flash_ptr[offset<<flash_info[chip_id].is_16bit] = data;
}