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
typedef  int /*<<< orphan*/  uintmax_t ;
typedef  scalar_t__ uint32_t ;
struct i40e_osdep {scalar_t__ mem_bus_space_size; int /*<<< orphan*/  mem_bus_space_handle; int /*<<< orphan*/  mem_bus_space_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ bus_space_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static __inline uint32_t
rd32_osdep(struct i40e_osdep *osdep, uint32_t reg)
{

	KASSERT(reg < osdep->mem_bus_space_size,
	    ("ixl: register offset %#jx too large (max is %#jx)",
	    (uintmax_t)reg, (uintmax_t)osdep->mem_bus_space_size));

	return (bus_space_read_4(osdep->mem_bus_space_tag,
	    osdep->mem_bus_space_handle, reg));
}