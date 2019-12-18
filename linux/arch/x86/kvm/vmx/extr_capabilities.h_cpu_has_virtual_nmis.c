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
struct TYPE_2__ {int pin_based_exec_ctrl; } ;

/* Variables and functions */
 int PIN_BASED_VIRTUAL_NMIS ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline bool cpu_has_virtual_nmis(void)
{
	return vmcs_config.pin_based_exec_ctrl & PIN_BASED_VIRTUAL_NMIS;
}