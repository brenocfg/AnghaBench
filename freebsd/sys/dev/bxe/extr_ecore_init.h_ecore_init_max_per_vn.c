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
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int quota; scalar_t__ rate; } ;
struct rate_shaping_vars_per_vn {TYPE_1__ vn_counter; } ;

/* Variables and functions */
 int RS_PERIODIC_TIMEOUT_USEC ; 

__attribute__((used)) static inline void ecore_init_max_per_vn(uint16_t vnic_max_rate,
				  struct rate_shaping_vars_per_vn *ram_data)
{
	/* global vnic counter */
	ram_data->vn_counter.rate = vnic_max_rate;

	/*
	* maximal Mbps for this vnic
	* the quota in each timer period - number of bytes
	* transmitted in this period
	*/
	ram_data->vn_counter.quota =
		RS_PERIODIC_TIMEOUT_USEC * (uint32_t)vnic_max_rate / 8;
}