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
typedef  enum ibv_port_state { ____Placeholder_ibv_port_state } ibv_port_state ;

/* Variables and functions */
#define  IBV_PORT_ACTIVE 131 
#define  IBV_PORT_ARMED 130 
#define  IBV_PORT_DOWN 129 
#define  IBV_PORT_INIT 128 

__attribute__((used)) static const char *port_state_str(enum ibv_port_state pstate)
{
	switch (pstate) {
	case IBV_PORT_DOWN:   return "PORT_DOWN";
	case IBV_PORT_INIT:   return "PORT_INIT";
	case IBV_PORT_ARMED:  return "PORT_ARMED";
	case IBV_PORT_ACTIVE: return "PORT_ACTIVE";
	default:              return "invalid state";
	}
}