#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {scalar_t__ address; } ;
struct TYPE_4__ {TYPE_1__ gaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_2__ residency_info_mem ; 

int lpit_read_residency_count_address(u64 *address)
{
	if (!residency_info_mem.gaddr.address)
		return -EINVAL;

	*address = residency_info_mem.gaddr.address;

	return 0;
}