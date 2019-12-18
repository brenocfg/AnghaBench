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
typedef  int bhnd_port_type ;

/* Variables and functions */
#define  BHND_PORT_AGENT 130 
#define  BHND_PORT_BRIDGE 129 
#define  BHND_PORT_DEVICE 128 

const char *
bhnd_port_type_name(bhnd_port_type port_type)
{
	switch (port_type) {
	case BHND_PORT_DEVICE:
		return ("device");
	case BHND_PORT_BRIDGE:
		return ("bridge");
	case BHND_PORT_AGENT:
		return ("agent");
	default:
		return "unknown";
	}
}