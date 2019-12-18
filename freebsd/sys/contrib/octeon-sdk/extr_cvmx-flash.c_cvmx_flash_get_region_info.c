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
typedef  int /*<<< orphan*/  cvmx_flash_region_t ;
struct TYPE_2__ {int /*<<< orphan*/  const* region; } ;

/* Variables and functions */
 TYPE_1__* flash_info ; 

const cvmx_flash_region_t *cvmx_flash_get_region_info(int chip_id, int region)
{
    return flash_info[chip_id].region + region;
}