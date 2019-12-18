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
struct TYPE_2__ {int bootloader_config_flags; } ;

/* Variables and functions */
 int CVMX_BOOTINFO_CFG_FLAG_DEBUG ; 
 TYPE_1__* cvmx_sysinfo_get () ; 

__attribute__((used)) static inline int cvmx_debug_booted(void)
{
    return cvmx_sysinfo_get()->bootloader_config_flags & CVMX_BOOTINFO_CFG_FLAG_DEBUG;
}