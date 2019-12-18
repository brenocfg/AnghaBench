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
typedef  int u8 ;
typedef  enum ib_port_state { ____Placeholder_ib_port_state } ib_port_state ;

/* Variables and functions */
 int IB_PORT_ACTIVE ; 

__attribute__((used)) static u8 state_to_phys_state(enum ib_port_state state)
{
	return state == IB_PORT_ACTIVE ? 5 : 3;
}