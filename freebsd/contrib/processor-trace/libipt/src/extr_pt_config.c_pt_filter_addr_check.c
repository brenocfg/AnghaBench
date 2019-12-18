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
typedef  int /*<<< orphan*/  uint64_t ;
struct pt_conf_addr_filter {int dummy; } ;

/* Variables and functions */
 int pt_filter_check_cfg_filter (struct pt_conf_addr_filter const*,int /*<<< orphan*/ ) ; 
 int pt_filter_check_cfg_stop (struct pt_conf_addr_filter const*,int /*<<< orphan*/ ) ; 

int pt_filter_addr_check(const struct pt_conf_addr_filter *filter,
			 uint64_t addr)
{
	int status;

	status = pt_filter_check_cfg_stop(filter, addr);
	if (status <= 0)
		return status;

	return pt_filter_check_cfg_filter(filter, addr);
}