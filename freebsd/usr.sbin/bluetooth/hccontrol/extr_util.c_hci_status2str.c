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

/* Variables and functions */
 int SIZE (char const* const*) ; 

char const *
hci_status2str(int status)
{
	static char const * const       t[] = {
		/* 0x00 */ "No error",
		/* 0x01 */ "Unknown HCI command",
		/* 0x02 */ "No connection",
		/* 0x03 */ "Hardware failure",
		/* 0x04 */ "Page timeout",
		/* 0x05 */ "Authentication failure",
		/* 0x06 */ "Key missing",
		/* 0x07 */ "Memory full",
		/* 0x08 */ "Connection timeout",
		/* 0x09 */ "Max number of connections",
		/* 0x0a */ "Max number of SCO connections to a unit",
		/* 0x0b */ "ACL connection already exists",
		/* 0x0c */ "Command disallowed",
		/* 0x0d */ "Host rejected due to limited resources",
		/* 0x0e */ "Host rejected due to security reasons",
		/* 0x0f */ "Host rejected due to remote unit is a personal unit",
		/* 0x10 */ "Host timeout",
		/* 0x11 */ "Unsupported feature or parameter value",
		/* 0x12 */ "Invalid HCI command parameter",
		/* 0x13 */ "Other end terminated connection: User ended connection",
		/* 0x14 */ "Other end terminated connection: Low resources",
		/* 0x15 */ "Other end terminated connection: About to power off",
		/* 0x16 */ "Connection terminated by local host",
		/* 0x17 */ "Repeated attempts",
		/* 0x18 */ "Pairing not allowed",
		/* 0x19 */ "Unknown LMP PDU",
		/* 0x1a */ "Unsupported remote feature",
		/* 0x1b */ "SCO offset rejected",
		/* 0x1c */ "SCO interval rejected",
		/* 0x1d */ "SCO air mode rejected",
		/* 0x1e */ "Invalid LMP parameters",
		/* 0x1f */ "Unspecified error",
		/* 0x20 */ "Unsupported LMP parameter value",
		/* 0x21 */ "Role change not allowed",
		/* 0x22 */ "LMP response timeout",
		/* 0x23 */ "LMP error transaction collision",
		/* 0x24 */ "LMP PSU not allowed",
		/* 0x25 */ "Encryption mode not acceptable",
		/* 0x26 */ "Unit key used",
		/* 0x27 */ "QoS is not supported",
		/* 0x28 */ "Instant passed",
		/* 0x29 */ "Pairing with unit key not supported"
	};

	return (status >= SIZE(t)? "Unknown error" : t[status]);
}