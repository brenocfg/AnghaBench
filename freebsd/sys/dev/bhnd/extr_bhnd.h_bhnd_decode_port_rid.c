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
typedef  int /*<<< orphan*/  bhnd_port_type ;

/* Variables and functions */
 int BHND_BUS_DECODE_PORT_RID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
bhnd_decode_port_rid(device_t dev, int type, int rid, bhnd_port_type *port_type,
    u_int *port, u_int *region)
{
	return BHND_BUS_DECODE_PORT_RID(device_get_parent(dev), dev, type, rid,
	    port_type, port, region);
}