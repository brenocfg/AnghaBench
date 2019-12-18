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

/* Variables and functions */

__attribute__((used)) static const char *
format_opt_class(uint16_t opt_class)
{
    switch (opt_class) {
    case 0x0100:
        return "Linux";
    case 0x0101:
        return "Open vSwitch";
    case 0x0102:
        return "Open Virtual Networking (OVN)";
    case 0x0103:
        return "In-band Network Telemetry (INT)";
    case 0x0104:
        return "VMware";
    default:
        if (opt_class <= 0x00ff)
            return "Standard";
        else if (opt_class >= 0xfff0)
            return "Experimental";
    }

    return "Unknown";
}