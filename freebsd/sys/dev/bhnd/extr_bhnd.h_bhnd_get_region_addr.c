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
typedef  int /*<<< orphan*/  u_int ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bhnd_size_t ;
typedef  int /*<<< orphan*/  bhnd_port_type ;
typedef  int /*<<< orphan*/  bhnd_addr_t ;

/* Variables and functions */
 int BHND_BUS_GET_REGION_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhnd_get_region_addr(device_t dev, bhnd_port_type port_type, u_int port,
    u_int region, bhnd_addr_t *region_addr, bhnd_size_t *region_size)
{
	return BHND_BUS_GET_REGION_ADDR(device_get_parent(dev), dev, port_type,
	    port, region, region_addr, region_size);
}