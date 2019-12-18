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
typedef  int u64 ;
struct TYPE_2__ {scalar_t__ basic_cap; } ;

/* Variables and functions */
 int VMX_BASIC_INOUT ; 
 TYPE_1__ vmcs_config ; 

__attribute__((used)) static inline bool cpu_has_vmx_basic_inout(void)
{
	return	(((u64)vmcs_config.basic_cap << 32) & VMX_BASIC_INOUT);
}