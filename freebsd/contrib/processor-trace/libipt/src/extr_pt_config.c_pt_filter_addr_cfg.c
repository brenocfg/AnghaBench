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
typedef  int uint8_t ;
typedef  unsigned int uint32_t ;
struct TYPE_2__ {int addr_cfg; } ;
struct pt_conf_addr_filter {TYPE_1__ config; } ;

/* Variables and functions */
 int pt_filter_addr_ncfg () ; 

uint32_t pt_filter_addr_cfg(const struct pt_conf_addr_filter *filter, uint8_t n)
{
	if (!filter)
		return 0u;

	if (pt_filter_addr_ncfg() <= n)
		return 0u;

	return (filter->config.addr_cfg >> (4 * n)) & 0xf;
}