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
typedef  int uint16_t ;
struct ena_admin_host_info {int bdf; } ;

/* Variables and functions */
 int ENA_ADMIN_HOST_INFO_DEVICE_MASK ; 
 int ENA_ADMIN_HOST_INFO_DEVICE_SHIFT ; 

__attribute__((used)) static inline void set_ena_admin_host_info_device(struct ena_admin_host_info *p, uint16_t val)
{
	p->bdf |= (val << ENA_ADMIN_HOST_INFO_DEVICE_SHIFT) & ENA_ADMIN_HOST_INFO_DEVICE_MASK;
}